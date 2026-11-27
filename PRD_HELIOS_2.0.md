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
| Forsyning i standby | MCU'en er forsynet i standby og ligger i deep sleep eller IDLE (§4.1). Forskel fra [D333], hvor U3 mister forsyningen. |
| INT0 | Udgang af en AND-gate med indgange fra on/off-knap, IR og 12V-link (bekræftet af Michael 2026-11-27). Vækker fra deep sleep på faldende flanke (`INT0EP` = 0, `plib_evic.c:57`). Når 12V-linket er aktivt, holdes udgangen lav, og der kommer ingen flanke (`On_Off_Control.c:1153`). Indgangenes polaritet er udledt af koden og ikke tjekket i diagrammet. |
| GPIO ind (power) | `ON_OFF_BUTTON` RJ15 (CN, høj = trykket), `LINK_12V` RB4 (aktiv lav), `IR_RC5` RH11 (CN), `AC_RESULT` RE8 (1 = `VoltageLow`, 0 = `VoltageHigh`), `AC_RESET` RC4 (høj = venstre forsyning til stede), `ACTIVATE_BOOTLOADER` (CN) (`plib_gpio.h`, `ac_check.h:39-49`) |
| GPIO ud (power) | `DPS_RELAY_ON_OFF` RG8, `SOFT_START_ON_OFF` RG7, `SP_RELAY` RB2 (sat = `VoltageLow`), `ONSTBY_LED`, `GAD_LOGO`, `GLCD_DISP_ON_STBY`, `DRV_TOUCH_PIN_RESET` (`plib_gpio.h`, `ac_check.c:84-87`) |

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
  her. Område 2: sleep-kaldet og UART-drænet før sleep (§4.1). _(Område 5: IR-sampling er
  kandidat, som i [D333].)_
- **NFR-012:** Alle I²C-transaktioner har eksplicit timeout og returnerer en statuskode
  (I2C-001/005; legacy: #3).
- **NFR-013:** Watchdog er DMT, tændt fra software med BTL 1.0's config
  (`FDMTEN=OFF`, `DMTCNT=DMT31`, `DMTINTV=WIN_127_128`; WDT-001/002). Detaljer følger
  [D333] NFR-013. Følgerne af sleep i standby står i §4.1. Legacy: WDT og DMT er slået fra
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
| 2 | §4.1 Power | `On_Off_Control.c`, `ac_check.c`, `voltageSetting.c`, `ui_voltage_Error.c` | Gennemgået 2026-11-27 |
| 3 | §4.2–4.3 Input, level, level match | `Level_Control.c`, `Screen_Input_Level_Match.c`, `Screen_Volume_Settings.c` | |
| 4 | §4.6 DAC og U26 | `Dac_Control.c`, `MB_IOexp_U26_Control.c`, `Screen_Digital_Setup.c` | |
| 5 | §4.9 IR | `IR_control.c`, `Screen_IR_Source_Setup.c` | |
| 6 | §4.10 GUI | `screen_Action.c` og øvrige `Screen_*.c` | |
| 7 | §4.11 Persistens | `eeProm_Functions.c` | |
| 8 | §4.12 UART-testinterface | `uart_control.c` | |
| 9 | §4.14 Servicestick | `app_usb_cmd.c` | |

### 4.1 Power-styring

_Område 2._ Auto Standby (FR-107) beskrives her, jf. #1.

**Legacy: standby-model (kode læst).** Hovedforskellen fra [D333]: MCU'en har forsyning i
standby.

- **Normal sluk:** MCU'en går i deep sleep og vækkes af INT0 (`On_Off_Control.c:1172-1182`).
- **Manuel sluk (knap eller IR), mens 12V-linket er aktivt:** MCU'en går i IDLE med CN-wake
  på knap og IR, fordi INT0 ikke giver en flanke (`:1152-1171`). IDLE beholder RAM, så
  blokeringen af 12V-linket (`pwrPolicy.link_blocked`) overlever. Efter opvågning fortsætter
  koden efter `POWER_LowPowerModeEnter` (`:1184-1189`).
- **Opvågning fra deep sleep er et reset.** Hele boot-stien køres, og `initAmp()` afgør,
  hvad der skal ske (`:588-630`):
  1. 12V-linket er aktivt (to samples med 50 ms imellem): ON.
  2. Vækkekilden er ikke `DSINT0` (fx første nettilslutning): tilbage i sleep.
  3. Ellers kaldes `wakeUp()`, som leder efter en gyldig årsag: IR-kode `KeyOnOff`
     (poll i 500 ms), knap (20 ms debounce) eller 12V-link (20 ms debounce, kun hvis det
     ikke er blokeret). En noise-guard sender enheden tilbage i sleep, hvis der ikke er
     fundet en årsag inden for 500 ms (`:696-784`).
- **Følger for genbrug af [D333]:**
  - D333 har ingen sleep-kode, så standby-mekanismen er Helios-specifik.
  - D333's reboot-loft (NFR-013) passer, fordi den persistente RAM heller ikke overlever
    deep sleep. Hver tænding går gennem boot-stien, som på D333.
  - Reset-årsagen ved en normal tænding er deep-sleep-opvågning og ikke POR.
  - DMT tæller ikke i IDLE og deep sleep, fordi der ikke hentes instruktioner.

**Legacy: ON-sekvens (kode læst).** Tilstandsmaskine `onOffSekvens` (`:1194-1253`), hvor
ventetiderne er one-shot `SYS_TIME`-callbacks (`:848-855`):

| Trin | Handling | Venter derefter | Kilde |
|---|---|---|---|
| AC-check | Logo tændt. Forventet spænding fra EEPROM; HIGH, hvis feltet ikke er sat. Ved match sættes `SP_RELAY`, ON/STBY-LED tændes, og sekvensen fortsætter. Ved mismatch, se AC-kontrol nedenfor. | — | `:1198-1241`, `ac_check.c:72-124` |
| ON1 | Green bias fra, `DPS_RELAY_ON_OFF` til, backlight-PWM, touch ud af reset, display til, `startupFlg = 1`, logo blinker hvert 250 ms | 500 ms | `:857-906` |
| ON2 | `Legato_Initialize()` | 500 ms | `:908-915` |
| ON3 | Backlight fades ind, `SOFT_START_ON_OFF` til | 1500 ms | `:917-926` |
| ON4 | EEPROM-værdier (defaults, hvis `curInp > 11`), inputnavne, `curLvl = startLvl`, IR-interrupt til, `powerOnFlg = 1`, init af U20/U16/U26, green bias efter niveau, USB-tændingstæller, boot-tæller i EEPROM | 3000 ms | `:928-970` |
| ON5 | `errorCheckFlg = 1`, amp-status, moduldetektion via U26, DAC-konfiguration, inputvalidering | 18 000 ms, eller 23 000 ms med phono-modul og `curInp == 6` | `:972-1055` |
| ON6 | Backlight fades ud til 0 | 1000 ms | `:1057-1066` |
| ON7 | Simple view (med dim-timer) eller action-skærm, logoet stopper med at blinke og lyser fast, `startupFlg = 0`, `outputMuteOff()`, `setInput()`, `#0:01;` på UART | 500 ms | `:1068-1095` |
| ON8 | `setDisplayIntensity()` | — | `:1096-1100` |

Fra AC-check til ON7 tager det ca. 25 s, og 30 s med phono. `powerOnFlg` sættes allerede i
ON4, mens `startupFlg` stadig er sat.

**Legacy: OFF-sekvens (kode læst).** OFF kører i ét blokerende kald, `handleOffSekvens1`
(`:1101-1190`):

1. Alle timere lukkes. Mute og output-mute til. Aktuelt input og digital setup gemmes.
   `errorCheckFlg = 0`, backlight 0.
2. 5 ms, derefter `SOFT_START_ON_OFF` af og `DPS_RELAY_ON_OFF` af. Touch i reset, display
   af, ON/STBY-LED og logo slukkes.
3. 700 ms, derefter ryddes `menuFlg`, `powerOnFlg` og `startupFlg`. `#0:00;` sendes på UART,
   og USB-kommandotilstanden ryddes.
4. 50 ms, derefter IR-interrupt fra og INT0-flaget ryddes. Deep sleep eller IDLE som
   beskrevet ovenfor, efter yderligere 50 ms.

Koden har ingen `PWR_DWN_OK`-handshake og skifter ikke mellem lineær forsyning og
switchmode-forsyning, som [D333] gør.

**Legacy: hvad der udløser sluk (kode læst).**

- **On/off-knap (CN):** kun i ON, med 20 ms debounce i ISR (`:289-299`).
- **IR `KeyOnOff`:** kun i ON (`IR_control.c:123-141`).
- **12V-linket falder:** debounced i 30 ms, i ON og under opstart, uanset hvad der tændte
  (`:113-159`, `:213-223`).
- **Venstre forsyning falder ud:** `AC_RESET` er lav i 5 polls med 10 ms imellem
  (`:1255-1309`).

Desuden gælder for 12V-linket: en manuel sluk, mens linket er aktivt, blokerer for at linket
tænder igen, indtil det har været inaktivt (`:170-195`, `:225-231`).

**Legacy: AC-kontrol (kode læst).**

- `AC_ReadActualFromPins()` giver `leftMissing`, hvis `AC_RESET` er lav, og ellers
  `AC_RESULT` (`ac_check.h:43-49`).
- **Ved mismatch:**
  - Displayet tændes direkte, uden tænd-sekvensen.
  - Skærmen er `leftPowerMissingScreen`, hvis venstre forsyning mangler, og ellers
    `wrongAcVoltageScreen` (`ac_check.c:131-146`, `app.c:51-65`).
  - ON/STBY-LED'en skifter tilstand hvert 1000 ms, dvs. 2 s periode ([D333] FR-108 skriver
    1 Hz).
  - Spændingen tjekkes igen hvert 200 ms. Når den matcher, laves et software-reset
    (`ac_check.c:126-174`).
  - Bootloader-aktivering virker fortsat (`ac_check.c:152-154`).
  - `UI_ShowVoltageError()` er en stub, der kun tænder display og logo og skriver en
    debug-linje (`ui_voltage_Error.c:5-18`).
- **Spændingssettingen** ligger i EEPROM (`voltageSetting.c`) og kan omprogrammeres via
  USB-kommandofilen (`app_usb_cmd.c:157`, `:345`). Er feltet ikke sat, bruges HIGH, og der
  skrives intet til EEPROM (`On_Off_Control.c:1207-1209`, `voltageSetting.h:26-28`).

**Krav til 2.0.** Mekanismen er [D333]'s `svc_power` (§8): en tick-baseret state machine med
tidsstempler, ikke `SYS_TIME`-callbacks. Trin, rækkefølge og tider er Helios' egne.

- **FR-100 (ON-sekvens):** Trinene AC-check og ON1–ON8 udføres i samme rækkefølge og med
  samme ventetider som i legacy-tabellen ovenfor (§5). Rækkefølgen af relæer og forsyninger
  er hardwarebeskyttelse og ændres ikke. `#0:01;` sendes i ON7.
- **FR-101 (stabilisering):** ON5 venter 18 s, eller 23 s, når phono-modulet er monteret og
  det validerede input er 6. [D333]'s 21/31 s bruges ikke.
- IR og persistens under opstart fastlægges i område 5 og 7.
- **FR-105 (OFF-sekvens):** Trinene og deres rækkefølge er som i legacy (§4.1), men tick-
  baseret.
  - Der gemmes efter §9.8.
  - `#0:00;` sendes, og UART'en drænes, før MCU'en går i sleep.
  - Bagefter følger standby efter FR-120.
- **FR-106 (hvad der udløser sluk):**
  - (a) On/off-knap i ON, 20 ms debounce.
  - (b) IR `KeyOnOff` i ON.
  - (c) Faldende flanke på 12V-linket i ON og under opstart, 30 ms debounce, uanset hvad der
    tændte.
  - (d) Udfald af venstre forsyning: `AC_RESET` lav i 5 × 10 ms, én gang pr. ON-periode
    (§9.7).
  - (e) Auto Standby (FR-107).

  Eventuelle fejl-triggere fastlægges i område 4.
- **FR-107 (Auto Standby):** 1:1 som [D333] FR-107. Nedtællingen løber kun i RUNNING, dvs.
  fra ON7 er nået og til en OFF-sekvens starter. **Udløber den, mens 12V-linket er aktivt,
  behandles det som en manuel sluk** (FR-121; beslutning 2026-11-27). [D333] har ikke det
  tilfælde, for dér ejer U12 12V-linket.
- **FR-108 (AC-kontrol):** Kører ved hver tænding før ON1 og afgøres ved majoritet af
  `AC_RESULT` og `AC_RESET` (§9.4).
  - **Venstre forsyning mangler:** `leftPowerMissingScreen`.
  - **Spændingen afviger fra settingen:** `wrongAcVoltageScreen`.
  - **I begge fejltilfælde:**
    - Displayet tændes direkte, uden tænd-sekvensen, så de analoge trin aldrig tændes.
    - ON/STBY-LED'en skifter hvert 1000 ms.
    - Der gentjekkes hvert 200 ms, og der laves et software-reset ved match.
    - Bootloader-aktivering virker fortsat.
  - **Ved match:** `SP_RELAY` sættes efter settingen.
- **FR-111 (spændingssetting):** Ligger i EEPROM, seedes ved første boot (§9.5) og kan
  omprogrammeres via USB-stick (område 9). Adressen er Helios' eksisterende og fastlægges i
  område 7.
- **FR-120 (standby, Helios-specifik):**
  - **Efter OFF:** deep sleep, vækkes af INT0.
  - **Efter en manuel sluk med aktivt 12V-link:** IDLE, vækkes af CN på knap og IR.
  - **Efter opvågning fra deep sleep** træffes boot-beslutningen som i legacy:
    - 12V-linket er aktivt: ON.
    - Vækkekilden er ikke `DSINT0`: tilbage i sleep.
    - Ellers søges der en gyldig årsag (IR `KeyOnOff`, knap eller 12V-link) inden for
      noise-guarden på 500 ms, som evalueres i hvert tick (§9.6).
  - **Opvågning fra IDLE** behandles i main-loopet. ISR'en sætter kun et flag (NFR-010).
- **FR-121 (politik for 12V-linket):**
  - Et aktivt link (debounced) tænder, hvis det ikke er blokeret.
  - En faldende flanke slukker (FR-106c).
  - En manuel sluk (knap, IR eller Auto Standby) med aktivt link blokerer linket, indtil det
    har været inaktivt. Blokeringen ligger i RAM og overlever IDLE.

Undtagelser fra NFR-011 i område 2: kun selve sleep-kaldet (`POWER_LowPowerModeEnter`) og
drænet af UART'en før sleep. Al anden venten i ON og OFF er tilstande.

Følger for NFR-013:
- DMT tæller ikke i IDLE og deep sleep.
- Efter IDLE fortsætter main-loopet og clearer DMT som normalt.
- Efter deep sleep starter boot-stien forfra.
- Boot-linjen (HIL-003) skal skelne deep-sleep-opvågning fra POR og DMT-reset.

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
| TIM-xx | Poll af venstre forsyning | 10 ms × 5 samples | `On_Off_Control.c:1255-1256` |
| TIM-xx | Debounce af 12V-link (faldende flanke) | 30 ms | `On_Off_Control.c:116` |
| TIM-xx | ON-trin 1 / 2 / 3 / 4 | 500 / 500 / 1500 / 3000 ms | `On_Off_Control.c:900`, `:910`, `:921`, `:964` |
| TIM-xx | ON-trin 5, stabilisering (D333 `T_STAB`: 21/31 s) | 18 000 ms, phono 23 000 ms | `On_Off_Control.c:1028-1029` |
| TIM-xx | ON-trin 6 / 7 | 1000 / 500 ms | `On_Off_Control.c:1062`, `:1092` |
| TIM-xx | Logo-blink under opstart | 250 ms | `On_Off_Control.c:898` |
| TIM-xx | OFF: mute → forsyninger af / → `#0:00;` / → sleep | 5 / 700 / 50 + 50 ms | `On_Off_Control.c:1112`, `:1121`, `:1137`, `:1168`, `:1179` |
| TIM-xx | AC-mismatch: LED skifter / gentjek | 1000 / 200 ms | `ac_check.c:120-121` |

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
| Auto Standby | [D333] FR-107, FR-815, FR-816 (`app_standby.c`) | 1:1 (#1) | _tjekkes_ |
| Power-sekvenser som tick-baseret state machine | [D333] `svc_power.c` | Mekanisme; trin og tider fra Helios (§4.1) | _tjekkes_ |
| Standby i deep sleep/IDLE med opvågning via INT0/CN | Ingen i [D333] | Helios-specifik, bygges ud fra [LEGACY] | — |

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
4. **AC-kontrollen afgøres ved majoritet** (beslutning 2026-11-27). Legacy afgør spænding og
   "venstre forsyning mangler" på ét sample af `AC_RESULT` og `AC_RESET`. Den såkaldte
   50 ms-ventetid er i praksis 10 tik × 100 µs (`ac_check.c:94-98`, `:195-197`, `:107`).
   2.0 genbruger [D333] `SvcSystem_MeasureAcVariant` (`svc_system.c:68-113`: 9 samples med
   100 µs imellem, majoriteten afgør) og bruger samme majoritet på `AC_RESET`. Den synlige
   adfærd er den samme. Sample-antal og afstand skal bænktestes (D333 §11.9).
5. **(adfærd) Spændingssettingen seedes ved første boot** (beslutning 2026-11-27), som
   [D333] FR-111.
   - **Legacy:** Er feltet tomt (`0xFF`), bruges HIGH, og der skrives intet
     (`On_Off_Control.c:1207-1209`). En uprogrammeret enhed på et LOW-net viser derfor
     mismatch-skærmen.
   - **2.0:** Den målte majoritetsværdi (§9.4) skrives i feltet, og `SP_RELAY` sættes efter
     den.
   - **Ingen seeding uden venstre forsyning:** Mangler venstre forsyning (`AC_RESET` lav ved
     majoritet), seedes der ikke, og `leftPowerMissingScreen` vises som i legacy.
   - **Gemt værdi gælder:** Bagefter er EEPROM-værdien autoritativ, så et senere net med en
     anden spænding giver stadig mismatch.
   - **Omprogrammering:** sker via USB-stick som i dag.
6. **Noise-guarden udløber på et tick** (beslutning 2026-11-27).
   - **Legacy:** Udløbet tjekkes kun, når `wakeUp()` kaldes igen (`On_Off_Control.c:777`),
     og det sker kun ved en ny IR- eller INT0-hændelse eller et nyt knaptryk. Efter en
     støjopvågning uden en sådan hændelse bliver MCU'en vågen i standby (kode læst, ikke set
     på bænken).
   - **2.0:** Guarden evalueres i hvert tick i standby, så enheden altid er tilbage i sleep
     senest `NOISE_GUARD_MS` = 500 ms efter en opvågning uden en gyldig årsag.
   - **Synlig adfærd:** uændret.
7. **Udfald af venstre forsyning udløser sluk i hver ON-periode** (beslutning 2026-11-27).
   - **Legacy:** Låsen `OffSeqDoneFlg` nulstilles aldrig (`On_Off_Control.c:1270`, `:1304`).
     Deep sleep nulstiller den via reset, men IDLE-vejen gør ikke. Efter en manuel sluk med
     aktivt 12V-link ignoreres et nyt udfald derfor i næste ON-periode.
   - **2.0:** Låsen nulstilles ved starten af hver ON-sekvens.
8. **OFF gemmer kun uden for opstart** (beslutning 2026-11-27), som [D333] FR-105.
   - **Legacy:** Input og digital setup gemmes ved hver OFF, også under opstart
     (`On_Off_Control.c:1106-1107`). EEPROM læses allerede i `initAmp()` (`:622`), men under
     opstart kan RAM afvige fra EEPROM. Fx sætter ON5 `curInp` til 1, hvis det input, der
     var valgt sidst, kræver et modul, der mangler (`:1018-1024`).
   - **2.0:** Der gemmes kun, når indstillingerne er indlæst og opstarten er afsluttet.
9. **Død power-kode videreføres ikke** (beslutning 2026-11-27). Kun den levende AC-vej
   (`ACCHK_*`, §4.1) er spec. Følgende kan ikke nås og overføres ikke:
   - `APP_LEFT_AC_ERROR`, som kun sættes i den udkommenterede
     `WaitFor_AC_RESET_High_100ms` (`On_Off_Control.c:511`, `:520`). Dermed er
     `updateLeftAcMissingScreen` (`:449`, `app.c:266-268`), grenen i OFF (`:1143-1148`) og
     betingelsen i `initAmp` (`:600`) også døde.
   - `AC_CHECK()` (`:403-447`).
   - Mismatch-grenen i `onOffSekvens` (`:1231-1238`), fordi `ACCHK_Done()` kun er sand ved
     et OK-resultat.

   Ingen adfærd ændres.

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
