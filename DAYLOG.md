# DAYLOG — Helios SW58403

Overdragelsesfil mellem sessioner og maskiner. Nyeste dag øverst under **Log**.

## Status

- FW 1.0 er ude i marken. Den importerede 1.0-kode er tagget `v1.0` (`271ed26`), som er
  det faste sammenligningspunkt for 2.0.
  Det er ikke tjekket, om den er bit-identisk med det image, der er i marken.
- App og BTL bygger rent fra en frisk klon (bekræftet 2026-11-26), også efter oprydningen af
  backupfiler i `App/src`, og efter at `nbproject/Makefile-*.mk` er taget ud af git.
- Mål: FW 2.0 som en komplet ombygning med lagdeling og host-tests, som på
  Volante/D333. En UART-testramme skal med fra første version af 2.0
  (`knowledge/baenk-automatisering.md`).

## Næste skridt

1. **PRD for 2.0 (#1), branch `docs/prd-2.0`:** `PRD_HELIOS_2.0.md` har D333's skelet, og
   område 1 (eksekveringsmodellen) er gennemgået. Næste skridt er **område 2, power**
   (`On_Off_Control.c`, `ac_check.c`, `voltageSetting.c`, `ui_voltage_Error.c`) til §4.1 og §2.
   Tabellen i PRD'ens §4 viser rækkefølgen og status for område 1–9. Ét område giver én
   commit. Hver legacy-adfærd mærkes `kode læst fil:linje`, og det, der ligner en fejl, skal
   Michael placere i §9 (rettes) eller §10 (bevares). Afklar under område 2, om MCU'en går i
   deep sleep i standby (`POWER_DS_WakeupSourceGet`) eller mister forsyningen som på D333.
   Brug kommentaren på #1 (BTL 1.0's bindinger og kravene fra de fælles erfaringer) og #3
   (kendte fejl i 1.0).
2. **Forstudie for BTL 2.0 (#2):** Det er et separat spor, som ikke blokerer appen.
3. **Rettelser til fælles erfaringer, venter på Michaels ja:**
   - SVC-009 siger, at Helios kan resette under afspilning. Det sker ikke, for USB behandles
     kun i standby (`tasks.c:93`).
   - GUI-002 er for snæver. Composer kan også inkludere eksplicitte glyf-intervaller.

## Log

### 2026-11-27
- PRD for 2.0 er startet på branch `docs/prd-2.0` (`PRD_HELIOS_2.0.md`). Skelettet følger
  D333, og kravnumrene genbruger D333's numre, hvor områderne svarer til hinanden.
- Område 1 (eksekveringsmodel) er kode læst. Det nye fund i forhold til #3 er, at der
  udføres arbejde i interrupt-kontekst:
  - INT0 kører `wakeUp()` med IR-poll i op til 500 ms og 20 ms delays.
  - `SYS_TIME`-callbacks kalder Legato og backlight.
  - Bootloader-CN skriver `appData.state` fra ISR.

  Guarden i `app.c:187` er død kode. Det hele står i PRD §3.2 og §9.
- Beslutning: UART-testinterfacet er altid aktivt i 2.0, i alle tilstande (PRD §9.3).
- Ventende: claude-setup er 8 commits bagud og har ucommittede ændringer i `PLAN.md` og
  `README.md` på denne maskine. Ny erfaring efter vandmærket: WDT-005 (MX-specifik).

### 2026-11-26
- De fælles erfaringer er gennemgået mod 1.0 (kode læst, intet set på hardware). Vandmærket
  står i `CLAUDE.md`. Kendte fejl i 1.0 står i #3, som er reference og ikke rettes nu. Kravene
  til 2.0 og BTL 1.0's bindinger står i en kommentar på #1. Følgende gælder ikke for Helios:
  - USBH-001, USBH-002 og USBH-008, fordi Helios bruger USBHS og ikke drv_usbfs.
  - USBH-007, fordi MCU'en ikke styrer VBUS (`portPowerEnable = NULL`).
  - BTL-008, I2C-002 og WDT-004, som er PIC32MX-specifikke.
  - MCC-002, som er MX-specifik. På MZ gælder `PMDL1WAY = ON` i stedet.
  - HIL-007…010, PS-001…003 og PS-005, fordi der hverken er Arduino-rig eller PowerShell-scripts.

  GIT-001 og PS-004 er allerede opfyldt af `.gitattributes`.
- `CLAUDE.md` er rettet: BTL er genereret med MCC 5.6.2 / core 5.8.2 og ikke 5.6.4.
- Branch `cleanup/backupfiler`: Følgende 10 backupfiler er slettet fra `App/src`: `Ny mappe/` (4 filer),
  `bu/Dac_Control.c`, `IR_Control_bu.c`, `app_usb_cmd_BU.c`, `_On_Off_Control.c`,
  `screen_Action_clean.c` og `ir_control.zip`. `configurations.xml` nævner ingen af dem, ingen
  kildefil `#include`'r dem, og `Ny mappe/` står ikke i nogen include-sti. Filerne kan hentes
  tilbage fra `v1.0`. Michael har bekræftet, at App og BTL bygger rent efter oprydningen,
  og branchen er merget til `main`.
- Branch `chore/ignorer-makefiler`: MPLAB X skriver `nbproject/Makefile-*.mk` om ved hvert byg
  med maskinafhængig `ProjectDir` og flag-hashes. Filerne er derfor fjernet fra git og
  ignoreret (MCC-007). Michael har bekræftet, at en frisk klon uden dem bygger rent, både App
  og BTL. Branchen er merget til `main`.
- Rammen for 2.0 er besluttet (#1). 2.0 er en ny arkitektur med 1.0's adfærd, og Auto Standby
  er den eneste nye feature, 1:1 som på D333. D333 er skabelonen. Koden ligger i en ny mappe ved siden af `App/`.
  App 2.0 skal kunne installeres via BTL 1.0. En selvopdaterbar BTL 2.0 er et separat forstudie (#2).
- Repoet er sat op med `.gitignore` og `.gitattributes`, som følger Volantes regler.
  Byggeoutput, MCC-backups og lokal IDE-tilstand ignoreres. Al tekst gemmes som LF, og
  `*.cmd` og `*.bat` checkes ud som CRLF.
- `dist/` er ignoreret, så `FW58403_Ver_1.0.bin` er ikke i repoet. Det kan i stedet lægges i
  en GitHub Release.
- Michael har bekræftet, at App og BTL bygger rent fra en frisk klon.
