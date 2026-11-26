# DAYLOG — Helios SW58403

Overdragelsesfil mellem sessioner og maskiner. Nyeste dag øverst under **Log**.

## Status

- FW 1.0 er ude i marken. Den importerede 1.0-kode er tagget `v1.0` (`271ed26`), som er
  det faste sammenligningspunkt for 2.0.
  Det er ikke tjekket, om den er bit-identisk med det image, der er i marken.
- App og BTL bygger rent fra en frisk klon (bekræftet 2026-11-26), også efter oprydningen af
  backupfiler i `App/src`.
- Mål: FW 2.0 som en komplet ombygning med lagdeling og host-tests, som på
  Volante/D333. En UART-testramme skal med fra første version af 2.0
  (`knowledge/baenk-automatisering.md`).

## Næste skridt

1. **PRD for 2.0 (#1):** Rammebeslutningerne er truffet og står i issuet. Næste skridt er at
   gennemgå 1.0's adfærd modul for modul og derefter skrive PRD'en med D333 som skabelon.
   Start i en ny session.
2. **Fælles erfaringer:** Vandmærket står på "ingen endnu". Gennemgå de relevante filer i
   `claude-setup/knowledge/` mod projektet.
3. **Forstudie for BTL 2.0 (#2):** Det er et separat spor, som ikke blokerer appen.

## Log

### 2026-11-26
- Branch `cleanup/backupfiler`: Følgende 10 backupfiler er slettet fra `App/src`: `Ny mappe/` (4 filer),
  `bu/Dac_Control.c`, `IR_Control_bu.c`, `app_usb_cmd_BU.c`, `_On_Off_Control.c`,
  `screen_Action_clean.c` og `ir_control.zip`. `configurations.xml` nævner ingen af dem, ingen
  kildefil `#include`'r dem, og `Ny mappe/` står ikke i nogen include-sti. Filerne kan hentes
  tilbage fra `v1.0`. Michael har bekræftet, at App og BTL bygger rent efter oprydningen,
  og branchen er merget til `main`.
- Rammen for 2.0 er besluttet (#1). 2.0 er en ny arkitektur med 1.0's adfærd, og Auto Standby
  er den eneste nye feature, 1:1 som på D333. D333 er skabelonen. Koden ligger i en ny mappe ved siden af `App/`.
  App 2.0 skal kunne installeres via BTL 1.0. En selvopdaterbar BTL 2.0 er et separat forstudie (#2).
- Repoet er sat op med `.gitignore` og `.gitattributes`, som følger Volantes regler.
  Byggeoutput, MCC-backups og lokal IDE-tilstand ignoreres. Al tekst gemmes som LF, og
  `*.cmd` og `*.bat` checkes ud som CRLF.
- `dist/` er ignoreret, så `FW58403_Ver_1.0.bin` er ikke i repoet. Det kan i stedet lægges i
  en GitHub Release.
- Michael har bekræftet, at App og BTL bygger rent fra en frisk klon.
