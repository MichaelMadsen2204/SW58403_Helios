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

1. **PRD for 2.0 (#1), branch `docs/prd-2.0`:** Område 1–3 er gennemgået. I område 4 er
   legacy og afvigelser færdige (§4.6, §9.13–9.18, §10.2–10.3). Næste skridt er **krav til
   2.0 i §4.6**:
   - FR-203 (DAC-sekvens ved digitalt skift).
   - DAC-krav efter [D333] FR-400–406 med Helios' parametre: init, PCM-filter, DSD-lavpas,
     digital gain +6, lock-gate, USB-tilslutning og Fs-visning.
   - Green bias.
   - FR-106: ingen fejl-triggere fra legacy.
   - TIM-rækker i §5 og §8-rækker med D333's bænkstatus (#53).

   Derefter sættes område 4 til "Gennemgået" i tabellen i §4, og vi går videre til område 5
   (IR). §11.6 har tre hardwarespørgsmål til Michael (U26 bit 1.2, autoincrement på
   DAC-modulets expander, polariteten på green bias). Arbejdsgang:
   - Hver legacy-adfærd mærkes `kode læst fil:linje`.
   - Det, der ligner en fejl, placerer Michael i §9 (rettes) eller §10 (bevares), én ad gangen.
   - Brug kommentaren på #1 (BTL 1.0's bindinger og kravene fra de fælles erfaringer) og #3
     (kendte fejl i 1.0).
   **Genbrug af D333 (PRD §1):** Findes der en testet løsning i D333
   (`D:/MPLAB/d333/SW_U3_REBUILD`, samme MCU), så genbruges den. Find derfor D333's løsning
   for hvert område, og gennemgå 1.0 for Helios-specifikke forskelle. Ved konflikt gælder
   D333's kode og Helios 1.0's parametre, som brugeren kan mærke.
2. **Forstudie for BTL 2.0 (#2):** Det er et separat spor, som ikke blokerer appen.

## Log

### 2026-11-27 (område 4)
- Område 4 (DAC-modul, U26, digital setup og green bias): legacy er beskrevet i §4.6 (kode
  læst).
- §3.2 er rettet: amp-status polles også via `checkStatus()` i seks skærmtilstande.
- **D333-genbrug:** Det er samme DAC-modul med de samme adresser. `drv_es9039`,
  `drv_ak4118`, `drv_u26` og `svc_dac` er bænkbevist med Audio Precision (D333 #53).
- **Beslutninger:**
  - User-mute holder på tværs af digitale skift. Der unmutes kun i `svc_mute` med lock-gate
    på USB og uden mute-blip (§9.13).
  - Phono gendannes også uden DAC-modul (§9.14).
  - Fs opsamles i `svc_dac`, uafhængigt af skærmen (§9.15).
  - Fs-opslag tjekkes mod tabellens længde (§9.16).
  - Død kode droppes, og EEPROM 0x08 reserveres (§9.17).
  - Green bias på AV bruger 66 (§9.18).
  - Filtret går rundt på IR og stopper på touch (§10.2).
  - Green bias følger `curLvl` (§10.3).
- **Fælles erfaringer:** WDT-005 er afgjort og har givet et krav om reset-årsag i §4.12.
  Vandmærket er nu WDT-005. Tilføjelser til SVC-009 (Helios er ikke ramt) og GUI-002
  (glyf-intervaller) er skrevet i `claude-setup`.
- **Åbent:** expander-navne (§11.5) og hardwarespørgsmål (§11.6). Digital gain støtter 1 dB pr.
  trin (§11.4). FR-320 bruges ikke i D333.

### 2026-11-27 (område 3)
- Område 3 (input, volumen, level match, balance og AV) er gennemgået i PRD §4.2, §4.3, §3.3,
  §5, §8, §9.10–9.12, §10.1 og §11.4 (kode læst).
- **D333-genbrug:** `drv_volctl`, `svc_volume`, `svc_mute`, `svc_input` og `app_audio_ctrl`
  er bænkbevist på D333 (#54, #169, #170, #173–175).
- **Helios-parametre:**
  - 11 inputs, AV på input 3 og 4 med indeks 66, og −6 dB på input 4 og 5.
  - To expandere (L og R) med indeks 0–84 og make-before-break i tre faser på 2 ms.
  - Balance og start/max-grænserne 0–66 og 20–84.
- **Beslutninger:**
  - Relæ-indekset har altid loft ved 84 (§9.10).
  - Mute sætter niveauet til 0 før relæerne, som på D333 (§9.11). Helios er en forforstærker.
  - Ingen IR-guard under make-before-break (§9.12).
  - Balance bevares (§10.1).
  - Legato-kapaciteten afledes af bufferen (NFR-021).
- **Åbent:** Er det 1 dB pr. relæ-trin på Helios (§11.4)?
- FR-320 (balance) er et nyt nummer. Det er ikke tjekket, at D333 ikke bruger det.

### 2026-11-27 (område 2)
- Område 2 (power) er gennemgået i PRD §2, §4.1, §5, §8 og §9.4–9.9 (kode læst).
- **Standby på Helios:** MCU'en har forsyning i standby og ligger i deep sleep, eller i IDLE
  ved manuel sluk med aktivt 12V-link.
  - Opvågning fra deep sleep er et reset.
  - D333 har ingen tilsvarende kode, for dér ejer U12 tænd/sluk og 12V-linket.
- **INT0 er en AND-gate** af knap, IR og 12V-link. Signalerne er bekræftet af Michael;
  polariteten er udledt af koden og ikke tjekket i diagrammet.
- **Beslutninger (§9):**
  - AC-målingen afgøres ved majoritet som på D333.
  - Spændingssettingen seedes ved første boot.
  - Noise-guarden evalueres i hvert tick.
  - Låsen for venstre forsyning nulstilles i hver ON-periode.
  - OFF gemmer ikke under opstart.
  - Død power-kode videreføres ikke.
- **Beslutning:** Udløber Auto Standby, mens 12V-linket er aktivt, behandles det som en
  manuel sluk (FR-107/121).
- **Afvist kandidat:** Timer-handles i `SYS_TIME` er sikre mod genbrug, fordi handlet
  indeholder en token (`sys_time.c:137-147`, `:580`).

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
- Beslutning: Helios 2.0 genbruger D333's testede løsninger. Ved konflikt gælder D333's kode
  og Helios' parametre, som brugeren kan mærke (PRD §1 og §8).
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
