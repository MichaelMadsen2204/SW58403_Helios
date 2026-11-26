@echo off
rem === postbuild.cmd (universal, quotes fixed) ===============================
rem %1 = DISTDIR
rem %2 = PROJECTNAME
rem %3 = IMAGE_TYPE
rem %4 = OBJCOPY path (8.3 sti anbefales)
rem Danner: <binFileName><firmwareVersion>.bin fra app.h
rem ==========================================================================

setlocal enabledelayedexpansion

set "OUTDIR=%~1"
set "PROJNAME=%~2"
set "IMG=%~3"
set "OBJCOPY=%~4"

set "SCRIPT_DIR=%~dp0"
set "APP_H=%SCRIPT_DIR%\..\src\app.h"

echo [POSTBUILD] OUTDIR   = "%OUTDIR%"
echo [POSTBUILD] PROJNAME = "%PROJNAME%"
echo [POSTBUILD] IMG_TYPE = "%IMG%"
echo [POSTBUILD] OBJCOPY  = "%OBJCOPY%"
echo [POSTBUILD] SCRIPT   = "%SCRIPT_DIR%"
echo [POSTBUILD] APP_H    = "%APP_H%"

if not exist "%OUTDIR%" (
  echo [ERROR] OUTDIR findes ikke: "%OUTDIR%"
  exit /b 2
)
if not exist "%OBJCOPY%" (
  echo [ERROR] xc32-objcopy ikke fundet: "%OBJCOPY%"
  exit /b 3
)

if not exist "%APP_H%" (
  echo [INFO] Default APP_H ikke fundet, søger...
  for /f "delims=" %%P in ('dir /b /s "%SCRIPT_DIR%\app.h" 2^>nul') do (
    set "APP_H=%%P"
    echo [INFO] Fundet APP_H = "%APP_H%"
    goto :have_apph
  )
  echo [ERROR] app.h ikke fundet i "%SCRIPT_DIR%\..\src\app.h" eller via søgning.
  exit /b 4
)
:have_apph

set "HEXFILE=%OUTDIR%\%PROJNAME%.%IMG%.hex"
if not exist "%HEXFILE%" (
  echo [ERROR] HEX ikke fundet: "%HEXFILE%"
  dir /b "%OUTDIR%"
  exit /b 5
)

rem --- læs og rens begge defines fra app.h ---
call :get_define_value BINNAME binFileName "%APP_H%"
call :get_define_value FWVER   firmwareVersion "%APP_H%"

rem strip anførselstegn og whitespace
for %%V in (BINNAME FWVER) do (
  set "tmp=!%%V!"
  set "tmp=!tmp:"=!"
  for /f "tokens=* delims= " %%Z in ("!tmp!") do set "%%V=%%Z"
)

if not defined BINNAME (
  echo [ERROR] #define binFileName mangler i "%APP_H%".
  echo [TIP]   Eksempel:  #define binFileName "FW58102_Ver_"
  exit /b 6
)
if not defined FWVER (
  echo [ERROR] #define firmwareVersion mangler i "%APP_H%".
  echo [TIP]   Eksempel:  #define firmwareVersion "0.1"
  exit /b 7
)

set "OUTBIN=%BINNAME%%FWVER%.bin"
rem fjern ulovlige filnavnstegn
for %%C in (^< ^> ^: ^" ^/ ^\ ^| ^? ^*) do set "OUTBIN=!OUTBIN:%%C=!"

echo [POSTBUILD] Konverterer:
echo           IN  = "%HEXFILE%"
echo           OUT = "%OUTDIR%\%OUTBIN%"

"%OBJCOPY%" -I ihex -O binary "%HEXFILE%" "%OUTDIR%\%OUTBIN%"
if errorlevel 1 (
  echo [ERROR] objcopy fejlede.
  exit /b 8
)

if not exist "%OUTDIR%\%OUTBIN%" (
  echo [ERROR] Output-bin ikke dannet: "%OUTDIR%\%OUTBIN%"
  exit /b 9
)

echo [OK] Færdig: "%OUTDIR%\%OUTBIN%"
exit /b 0

:get_define_value
rem %1 = output var, %2 = define-navn, %3 = sti til app.h
set "%~1="
for /f "usebackq tokens=1,2,* delims= " %%A in (`findstr /R /C:"^[ 	]*#define[ 	][ 	]*%~2[ 	]" %~3`) do (
  set "rest=%%C"
  rem tag første token; klip ved " / ; , og tabs/spaces
  for /f "tokens=1 delims= ""/;, 	" %%V in ("!rest!") do set "%~1=%%V"
)
exit /b 0
