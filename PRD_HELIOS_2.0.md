# PRD — Helios SW58403 firmware 2.0

> Version 0.1 — udkast under opbygning (#1)
> Mål: en ny firmware med **funktionel paritet** med Helios FW 1.0 (tag `v1.0`, `271ed26`)
> på **uændret hardware**, med **Auto Standby** som eneste nye funktion.
>
> Normative referencer:
> - **[LEGACY]** `App/src/` på tag `v1.0` — adfærdsreference og orakel
> - **[D333]** `D:/MPLAB/d333/PRD_D333_REBUILD.md` — skabelon for arkitektur og krav
> - **[CONV]** Firmware Conventions — Gryphon Audio Embedded Projects (som i D333)
> - **[KNOW]** `claude-setup/knowledge/` — fælles erfaringer (ID'er som `MCC-006`)
>
> Nøgleord: **SKAL** = ufravigeligt krav. **BØR** = krav medmindre afvigelse begrundes.
> **KAN** = valgfrit. Krav er nummererede (`FR-xxx`, `NFR-xxx`, `TIM-xx`). Hvor et område
> svarer til D333, genbruges D333's nummer, så de to PRD'er kan krydsrefereres.
>
> Evidens for legacy-adfærd: **kode læst** `fil:linje` mod `v1.0`, medmindre andet står.
> Intet i dette dokument er set på hardware, før det er markeret **bænkbevist**.

---

## 1. Formål og scope

_Udfyldes. Kilde: beslutningerne i #1 (2026-11-26)._

- 2.0 er en ny arkitektur, der bevarer 1.0's adfærd. 1.0 er spec og orakel.
- **Auto Standby** er den eneste nye funktion og følger [D333] FR-107, FR-815 og FR-816 1:1.
- 2.0 ligger i en ny mappe ved siden af `App/` med eget MPLAB-projekt og `tests/`. `App/`
  (1.0) forbliver byggbar. Mappenavnet fastlægges her (åbent, §11).
- **Genbrug af D333 (beslutning 2026-11-27):** Helios og D333 kan sammenlignes på mange
  områder. Findes der en løsning i D333, som er implementeret og testet, bruger Helios 2.0
  den. Kilden er D333's rebuild af U3 (`D:/MPLAB/d333/SW_U3_REBUILD`, samme MCU). Gennemgangen
  af 1.0 skal derfor især finde de Helios-specifikke forskelle i hardware og adfærd.
  - **Ved konflikt** genbruges D333's kode og mekanisme, mens parametre, som brugeren kan
    mærke (tider, niveauer, tekster, skærmforløb), følger Helios 1.0. Eksempel: D333 dæmper
    efter 10 s, men Helios beholder 8 s (TIM-17).
  - En afvigelse, der ikke kan klares med en parameter, lægges frem for Michael og noteres
    i §9 eller §10.
  - Kun en løsning, der er bænkbevist eller i drift på D333, tæller som testet. Hvad der
    genbruges fra D333, og med hvilken status, står i §8.
- **Uden for scope:** bootloaderen (BTL 1.0 genbruges uændret, se §4.13; BTL 2.0 er #2),
  hardwareændringer og ny funktionalitet ud over paritet og Auto Standby.

---

## 2. Hardware-platform (fastlagt, må ikke ændres)

_Udfyldes under område 2–9 (busser, adresser, GPIO, interrupts)._

| Element | Beskrivelse |
|---|---|
| MCU | PIC32MZ2064DAR176, MPLAB Harmony 3, Legato GUI 480×272 (PDA TM4301B) |
| Toolchain | XC32 4.60, MPLAB X v6.25, DFP `PIC32MZ-DA_DFP` 1.5.231 |

---

## 3. Arkitekturkrav

### 3.1 Lagdeling (jf. [CONV] §1)

_Udfyldes, når modulopdelingen kendes (efter område 2–9). Skabelon: [D333] §3.1._

### 3.2 Eksekveringsmodel

**Legacy (kode læst):**

- Bare-metal superloop: `main()` kalder `SYS_Initialize`, derefter `initAmp()` og så
  `SYS_Tasks()` i en uendelig løkke (`main.c:42-54`).
- `SYS_Tasks()` i den genererede `tasks.c` er rettet i hånden (MCC-001):
  - `DRV_GLCD_Update()` køres kun, når `powerOnFlg || startupFlg || acErrorFlg` (`tasks.c:82-83`).
  - USB-host, USBHS-driver og `APP_USB_CMD_Tasks()` køres kun, når `!powerOnFlg`, dvs. i
    standby (`tasks.c:93-104`).
  - Rækkefølgen er `SYS_FS` → GLCD → touch → Legato → (USB) → `SYS_INP` → `APP_Tasks`.
- `APP_Tasks()` (`app.c:155-288`) kører hvert tik først en fast række services:
  `ServiceIr` → `onOffSekvens` → `showAcError`. Er `wakeUpFlg` sat, returneres der her
  (`app.c:166-167`). Ellers følger `PollPowerInputs_12V_ForOff` → `checkForLeftPSFallOut` →
  `screenSwap` → `saveDisp` → `irToggleMute` → `InputMute_Service` → `handleUIRequests`.
- Derefter en `switch` på `appData.state`, hvor tilstanden i praksis er "hvilken skærm er
  aktiv" (`APP_ACTION_SCREEN_TASKS`, `APP_SIMPLEVIEW_SCREEN_TASKS`, …; `app.h:241-256`).
  Tilstanden sættes 22 steder i 10 filer, og `APP_STATE_IDLE` bruges også som menu-tilstand
  (`app.c:116`).
- UART-kommandoer (`uartCtrl`) behandles kun i `APP_STATE_IDLE` og på action- og
  simple-view-skærmen efter opstart (`app.c:192`, `:214`, `:280`).
- Amp-status (U26-INT) polles kun i `APP_STATE_IDLE` (`app.c:273-278`).
- UI-skift sker delvist via en request-mekanisme (`appData.reqUiAction`, `handleUIRequests`,
  `app.c:73-142`), men ikke konsekvent (se interrupt-kontekst nedenfor).

**Legacy: arbejde i interrupt-kontekst (kode læst).** Alle ISR'er kører på IPL1
(`interrupts.c:93-168`). `SYS_TIME`-callbacks kaldes fra core-timer-ISR'en
(`sys_time.c:474`, via `SYS_TIME_PLIBCallback`). Følgende kører derfor i ISR:

| Handler | Hvad den gør | Kilde |
|---|---|---|
| INT0 `onOffButtonEventHandler` | Kalder `wakeUp()`, som kan polle IR i op til 500 ms (`IR_POLL_WINDOW_MS`) og vente 2×20 ms med `CORETIMER_DelayMs` | `On_Off_Control.c:303-315`, `:696-784` |
| CN `APP_PIN_Handler` (on/off-knap) | `CORETIMER_DelayMs(20)` som debounce, kalder `wakeUp()` eller starter OFF-sekvensen | `On_Off_Control.c:257-301` |
| CN `activateBootloaderEventHandler` | Skriver `appData.state = APP_ACTIVATE_BOOTLOADER` direkte | `On_Off_Control.c:235-239` |
| `actionViewTimeOut_Callback` | Kalder `legato_showScreen()` | `screen_Action.c:326-334` |
| `autoDispTimeOut_Callback` | Sætter backlight og kalder Legato-widgets | `screen_Action.c:336-` |
| `remoteViewDispDelay_Callback` | Kalder `SYS_TIME_TimerDestroy` | `IR_control.c:99-113` |
| `VolRepeat_Callback`, `VolInitialDelay_Callback` | Ændrer `curLvl` og registrerer nye timere; selve I²C-skrivningen sker i main-loopet (`ActionScreen_VolumeUiPump`) | `screen_Action.c:197-273` |

Øvrige callbacks sætter kun flag (`IR_control.c:66-77`, `ac_check.c:42-50`,
`On_Off_Control.c:1261-1265`, `Level_Control.c:15-18`, `eeProm_Functions.c:71-81`).

**Krav til 2.0:**

- **NFR-010:** Bare-metal superloop som legacy. Al applikationslogik kører som tick-baserede
  state machines fra main-loopet. ISR'er og `SYS_TIME`-callbacks sætter kun flag eller
  tidsstempler ([CONV] §3–4). De kalder aldrig Legato, I²C, backlight, `printf`, delays eller
  `SYS_TIME`-API'er, og de skriver aldrig til en tilstandsvariabel, som main-loopet også
  skriver.
- **NFR-011:** Ingen blokerende delays i normal drift. Ventetider er state-machine-tilstande
  med sammenligning af tidsstempler. Undtagelser markeres `// CONVENTION-EXCEPTION:` og står
  her. _(Liste udfyldes under område 2 og 5: OFF-sekvensens sidste fase og IR-sampling er
  kandidater, som i [D333].)_
- **NFR-012:** Alle I²C-transaktioner har eksplicit timeout og returnerer en statuskode
  (I2C-001/005; legacy: #3).
- **NFR-013:** Watchdog er DMT, tændt fra software med BTL 1.0's config
  (`FDMTEN=OFF`, `DMTCNT=DMT31`, `DMTINTV=WIN_127_128`; WDT-001/002). Detaljer følger
  [D333] NFR-013 og fastlægges under område 2. Legacy: WDT og DMT er slået fra
  (`initialization.c:87,90`).
- **NFR-014:** Én fælles tidskilde `NowMs()` baseret på `SYS_TIME_Counter64Get()` eller
  tællerdifferencer (MCC-006). Legacy har flere `millis()`-varianter, der wrapper (#3).
- **NFR-015:** Ingen egen logik i genereret kode (MCC-001). Det, legacy har lagt i `tasks.c`
  (GLCD- og USB-gating efter power-tilstand), flyttes til Application Layer.
- **NFR-016:** Applikationstilstand og aktiv skærm er adskilte begreber. Power-tilstand,
  menu/normal drift og aktiv skærm modelleres hver for sig, og kun GUI Layer kender
  skærm-ID'er.
- **NFR-017:** Kildefiler er UTF-8. Legacy-filerne er Windows-1252 (fx `app.c`), så æ, ø og
  å i kommentarer bliver ødelagt ved kopiering.

### 3.3 Legato widget-sikkerhed

- **NFR-020:** [CONV] §10 (Legato) er ufravigelig: intet widget tilgås, medmindre dets skærm
  er current, og kun fra main-loopet. Legacy-guarden i `app.c:187`
  (`if (!legato_getCurrentScreen() == screenID_actionScreen)`) er død kode: `!x` giver 0
  eller 1, og `screenID_actionScreen` er 2 (`le_gen_init.h:42`), så betingelsen er aldrig sand.
- GUI-idiomer, der skal bevares (GUI-001/002): _udfyldes under område 6._

---

## 4. Funktionelle krav

_Udfyldes område for område. Rækkefølge for gennemgangen:_

| Område | Afsnit | Legacy-filer | Status |
|---|---|---|---|
| 1 | §3.2 Eksekveringsmodel | `main.c`, `app.c`, `app.h`, `tasks.c` | Gennemgået 2026-11-27 |
| 2 | §4.1 Power | `On_Off_Control.c`, `ac_check.c`, `voltageSetting.c`, `ui_voltage_Error.c` | |
| 3 | §4.2–4.3 Input, level, level match | `Level_Control.c`, `Screen_Input_Level_Match.c`, `Screen_Volume_Settings.c` | |
| 4 | §4.6 DAC og U26 | `Dac_Control.c`, `MB_IOexp_U26_Control.c`, `Screen_Digital_Setup.c` | |
| 5 | §4.9 IR | `IR_control.c`, `Screen_IR_Source_Setup.c` | |
| 6 | §4.10 GUI | `screen_Action.c` og øvrige `Screen_*.c` | |
| 7 | §4.11 Persistens | `eeProm_Functions.c` | |
| 8 | §4.12 UART-testinterface | `uart_control.c` | |
| 9 | §4.14 Servicestick | `app_usb_cmd.c` | |

### 4.1 Power-styring

_Område 2._ Auto Standby (FR-107) beskrives her, jf. #1.

### 4.2 Input-styring

_Område 3._

### 4.3 Volumen og level match

_Område 3._

### 4.6 DAC-modul og U26

_Område 4._

### 4.9 IR-fjernbetjening

_Område 5._

### 4.10 GUI

_Område 6._ Auto Standby-overlay og menupunkt (FR-815, FR-816).

### 4.11 Persistens

_Område 7._ EEPROM-layout fra 1.0 og ledige adresser til Auto Standby står i #1.

### 4.12 UART-testinterface

_Område 8._ Skal opfylde HIL-003 (boot-linje med reset-årsag, livsprøve, faste fejlrammer).

### 4.13 Bootloader-kontrakt

App 2.0 SKAL kunne installeres via BTL 1.0. Bindingerne står i kommentaren på #1 og
overføres hertil (filnavn, image-start `0x9D000000`, hop-ord `0x9D000200`, frosne
config-ord, RAM-trigger `0x80000000–0F`).

### 4.14 USB-servicestick

_Område 9._

---

## 5. Timing-krav (samlet)

| ID | Parameter | Værdi | Reference |
|---|---|---|---|
| TIM-16 | `T_ACTIONVIEW` | 6 s (D333: 6 s) | `app.h:84` |
| TIM-17 | `T_DIM` | 8 s (Helios-værdi bevares; D333: 10 s) | `app.h:85` |
| TIM-xx | `T_SCREENSWAP` | 300 ms | `app.h:86` |
| TIM-xx | Debounce on/off-knap og 12V-link | 20 ms | `On_Off_Control.c:277`, `:743`, `:760` |
| TIM-xx | IR-poll-vindue ved opvågning | 500 ms | `IR_control.c:34` |
| TIM-xx | Noise-guard ved opvågning | 500 ms | `On_Off_Control.c:16` |
| TIM-xx | Poll af venstre forsyning | 10 ms | `On_Off_Control.c:1255` |

_Udvides under hvert område. Numre tildeles, når listen er komplet._

---

## 6. Fejlkode- og statusmodel

Som [D333] §6. _Helios-specifikke fejlkilder udfyldes under område 2 og 4._

---

## 7. Test-krav

_Udfyldes. Skabelon: [D333] §7. Bænktests skal automatiseres, hvor det kan lade sig gøre
(HIL-001…006)._

---

## 8. Migrerings- og genbrugskilder

D333-løsninger går forud for nyudvikling (§1). Helios-parametre kommer fra [LEGACY].

| Emne | Kilde | Genbrug | Status i D333 |
|---|---|---|---|
| Eksekveringsmodel, superloop med flag-ISR'er | [D333] NFR-010/011, `SW_U3_REBUILD` | Mekanisme 1:1 | _tjekkes_ |
| DMT-watchdog og reboot-loft | [D333] NFR-013 | 1:1 | Bænkbevist 2026-10-21 ([D333] NFR-013) |
| Auto Standby | [D333] FR-107, FR-815, FR-816 | 1:1 (#1) | _tjekkes_ |

_Udvides under område 2–9. "Tjekkes" betyder, at status skal læses i D333's repo eller
issues, før genbruget besluttes._

---

## 9. Bevidste afvigelser fra legacy

De fleste punkter er afvigelser i **implementering** og ikke i adfærd. Punkter, der ændrer
adfærd, er markeret **(adfærd)**.

1. **Intet arbejde i ISR (NFR-010).** Opvågning (`wakeUp`, IR-poll, debounce), skærmskift og
   backlight ved timeout samt bootloader-aktivering flyttes fra ISR til main-loopet. Den
   synlige adfærd (tider og rækkefølge) bevares. Kilde: tabellen i §3.2.
2. **Gating i `tasks.c` flyttes til Application Layer (NFR-015).** Samme adfærd: GLCD
   opdateres kun ved ON, opstart eller AC-fejl, og USB køres kun i standby.
3. **(adfærd) UART-testinterfacet er altid aktivt** (beslutning 2026-11-27). Parseren kører i
   alle tilstande: opstart, standby, menu og normal drift. Kommandoer, som tilstanden ikke
   tillader, afvises med en fast fejlramme, men ignoreres aldrig tavst. Livsprøve og
   statusforespørgsler svarer altid (HIL-003). Legacy behandler kun `uartCtrl` i
   `APP_STATE_IDLE` og på action- og simple-view-skærmen efter opstart (`app.c:192`, `:214`,
   `:280`). Hvilke kommandoer der er tilladt i hvilken tilstand, fastlægges i §4.12.

---

## 10. Adfærd der SKAL bevares, selv om den kan ligne en fejl

_Udfyldes under område 2–9._

---

## 11. Åbne spørgsmål

1. **Mappenavn** for 2.0 ved siden af `App/` (#1).
2. **Bit-identitet:** Er `v1.0` bit-identisk med det image, der er i marken? (#1)
3. **Kendte fejl og klager fra marken** er ikke samlet (#1). De er gode testcases.

---

*Dokumentet vedligeholdes efter samme meta-regel som [D333]: huller opdaget under
implementeringen rettes her, før koden skrives.*
