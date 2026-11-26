# CLAUDE.md — Helios SW58403

Firmware til Helios (Gryphon Audio). FW 1.0 er ude i marken. Version 2.0 bliver en
komplet ombygning (se `DAYLOG.md`).

## Projektet

- **MCU:** PIC32MZ2064DAR176 (PIC32MZ DA), DFP `PIC32MZ-DA_DFP` 1.5.231.
- **Toolchain:** XC32 **4.60**, MPLAB X v6.25, MCC 5.6.4 / core 5.8.4. Byg ikke med andre
  versioner. MCC-versionen står i regenererings-commit'en (MCC-008).
- **App:** `App/SW58403.X`, kilde i `App/src`. Legato GUI (480×272, PDA TM4301B), USB host
  MSD, I²C ×3, UART1.
- **BTL:** `BTL/SW58403BL.X`, kilde i `BTL/src`. Filsystem-bootloader over USB MSD.
- **Postbuild:** `App/SW58403.X/postbuild.cmd` danner `<binFileName><firmwareVersion>.bin`
  ud fra defines i `App/src/app.h`. Filen skal være CRLF (`.gitattributes`).
- **MCC-tilstand:** Den levende tilstand ligger i `<proj>.X/<proj>_default/` (`components/` +
  `mcc-config.mc4`). `*.bak*` er backups og aldrig kilde til en regenerering. BTL har ingen
  `SW58403BL.mc3`, kun en ignoreret `.bak0`.

## Sessionsstart

1. `git fetch --all --prune` og bekræft branch (`git branch --show-current`).
2. Læs **Status** og **Næste skridt** i `DAYLOG.md`.
3. Opgaver styres som GitHub issues; tjek de åbne før nyt arbejde startes.

## Byg

- Byg App og BTL i MPLAB X. En frisk klon bygger rent (bekræftet 2026-11-26).
- `src/config/` er MCC-genereret og rettes aldrig i hånden. Læs hele diffen efter en
  regenerering (MCC-001).
- Host-tests erstatter ikke target-verifikation. Påstå aldrig, at noget virker på
  hardware, før Michael har bekræftet det på bænken.

## Fælles erfaringer

Gennemgået til og med: ingen endnu.

Relevante filer i `D:/Github/claude-setup/knowledge/` for dette projekt: `mcc-harmony.md`,
`legato-gui.md`, `usb-host.md`, `bootloader.md`, `usb-servicestick.md`, `i2c.md`,
`watchdog.md`, `baenk-automatisering.md`. Format og regler: `knowledge/README.md`.

## Sessionsafslutning

Opdatér **Status** og **Næste skridt** i `DAYLOG.md`, commit og push. Uafsluttet arbejde
går på en feature-branch eller `wip/<YYYY-MM-DD>`, aldrig direkte på main.
