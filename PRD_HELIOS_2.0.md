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
| Produkt | Forforstærker. [D333] er en integreret forstærker (Michael 2026-11-27). |
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
- Amp-status (U26-INT) polles i `APP_STATE_IDLE` uden for opstart (`app.c:273-278`) og via
  `checkStatus()` i seks skærmtilstande (`app.c:191`, `:211`, `:223`, `:230`, `:237`, `:244`).
  Detaljer i §4.6.
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
- **NFR-021:** Den kapacitet, der gives til `leFixedString_Constructor`, afledes altid af
  bufferen (`sizeof(buf) / sizeof(buf[0])`) og skrives aldrig som et tal.
  - **Legacy:** Kapaciteten er 16, men bufferne har kun 9 elementer
    (`Screen_Input_Level_Match.c:13-18`, `:203-233`) og 8 elementer
    (`Screen_Volume_Settings.c:23-24`, `:146`, `:162`).
  - Der sker intet overløb i praksis, for den længste tekst er "+8 dB". Men den grænse,
    som Legato håndhæver, er forkert.
  - De øvrige `Screen_*.c` tjekkes i område 6.
- GUI-idiomer, der skal bevares (GUI-001/002): _udfyldes under område 6._

---

## 4. Funktionelle krav

_Udfyldes område for område. Rækkefølge for gennemgangen:_

| Område | Afsnit | Legacy-filer | Status |
|---|---|---|---|
| 1 | §3.2 Eksekveringsmodel | `main.c`, `app.c`, `app.h`, `tasks.c` | Gennemgået 2026-11-27 |
| 2 | §4.1 Power | `On_Off_Control.c`, `ac_check.c`, `voltageSetting.c`, `ui_voltage_Error.c` | Gennemgået 2026-11-27 |
| 3 | §4.2–4.3 Input, level, level match | `Level_Control.c`, `Screen_Input_Level_Match.c`, `Screen_Volume_Settings.c` | Gennemgået 2026-11-27 |
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

_Område 3._ [D333]-løsningen er `svc_input`, `svc_mute` og `app_audio_ctrl` (§8). Forskelle
fra [D333] står i klammer.

**Legacy: inputs (kode læst).**

- **11 inputs:**
  - 1–5 er analoge line-inputs.
  - 6 er phono og findes kun med phono-modul.
  - 7 er USB, og 8–11 er digitale. De findes kun med DAC-modul.
  - `maxInp` er 5, 6 med phono og 11 med DAC (`screen_Action.c:473-484`).
  - Uden phono, men med DAC, springes input 6 over ved op/ned (`IR_control.c:189-206`).

  [D333: 10 inputs.]
- **Relæer på U26, byte 0:** Et analogt input n sætter bit n−1. Alle digitale inputs deler
  bit 6 (`0x40`). Bit 7 er output-mute og bevares (`MB_IOexp_U26_Control.c:405-433`).
- **−6 dB-relæet** er til på input 4 og 5 (`:477`). [D333: input 3 og 4.]
- **Valg:** sker via touch (`screen_Action.c:610-628`), IR (direkte og op/ned,
  `IR_control.c:143-213`) og UART (`uart_control.c:348`, område 8). Op/ned wrapper ikke.
  IR-kode 0 vælger input 10, men kun med DAC (`IR_control.c:151-154`).
- **Validering ved tænding:** Mangler det modul, som det gemte input kræver, vælges input 1
  (`On_Off_Control.c:1020-1021`, `MB_IOexp_U26_Control.c:504-505`, `:530-531`).

**Legacy: inputskift (kode læst).** `setInput()` (`MB_IOexp_U26_Control.c:456-484`):

1. Er inputtet uændret, sker der intet.
2. Er det gamle eller det nye input analogt:
   - `muteOn()` åbner alle input-relæer, og DAC-kanalen mutes, hvis det gamle input var
     digitalt (`:259-271`).
   - Derefter venter koden 20 ms (blokerende).

   Ved digital → digital springes dette trin over.
3. Er det nye input digitalt, kaldes `setDigitalInput()` (område 4).
4. −6 dB-relæet sættes efter inputtet.
5. Et mute-vindue starter altid, også ved digital → digital. Det varer 2000 ms, hvis niveauet
   er over 0 eller inputtet er AV, og ellers 200 ms (`:479-481`).

**Legacy: når mute-vinduet udløber (kode læst).** `InputMute_Service()` kaldes i hvert loop
(`app.c:173`, `MB_IOexp_U26_Control.c:535-559`):

- Er niveauet over 0 eller inputtet AV, og er der ingen user-mute, så lukkes input-relæet, og
  AV-niveauet eller `UpdateVolume()` skrives.
- Ellers forbliver relæerne åbne.
- Så længe vinduet er åbent, ignoreres volumentrin fra touch og IR
  (`screen_Action.c:198`, `IR_control.c:169`, `:178`).

**Legacy: AV (kode læst).**

- Input 3 og/eller 4 kan udpeges som AV via masken `avInp` (`ScreenAV_Setup.h:7-16`).
  [D333: input 2 og/eller 3.]
- På et AV-input sættes begge kanaler til det faste relæ-indeks 66 (`avLevInp`, `app.h:152`).
  Balance, level match og digital gain bruges ikke (`Level_Control.c:202-233`).
  [D333: indeks 38.]
- Niveauvisningen og volumenknapperne skjules, og IR-volumen ignoreres
  (`screen_Action.c:808-815`, `:1376-1391`, `IR_control.c:169`, `:178`).
- Mute virker også på et AV-input (`screen_Action.c:529`).

**Krav til 2.0.** Mekanismen er [D333]'s `svc_input`, `svc_mute` og `app_audio_ctrl` (§8).
Inputs, relæbits og tider er Helios' egne.

- **FR-200 (inputs):** Der er 11 inputs som i legacy.
  - Input 6 kræver phono-modul, og input 7–11 kræver DAC-modul.
  - Mangler det modul, som det gemte input kræver, vælges input 1 ved tænding.
- **FR-201 (input-relæer):** Et analogt input n sætter bit n−1 i U26 byte 0. De digitale
  inputs deler bit 6. Bit 7 (output-mute) røres ikke.
- **FR-202 (inputskift):** Et skift er altid en transition-mute i `svc_mute` og blokerer
  aldrig (NFR-011).
  - Er det gamle eller det nye input analogt, mutes der efter §9.11. Ved digital → digital
    springes det analoge mute over, men holdet gælder stadig.
  - Holdet varer 2000 ms, hvis niveauet er over 0 eller inputtet er AV, og ellers 200 ms.
  - Under holdet ignoreres volumentrin.
  - Når holdet udløber, unmutes der kun, hvis niveauet er over 0 eller inputtet er AV, og
    der ikke er user-mute.
  - Legacy's blokerende ventetid på 20 ms bliver en tilstand.
- **FR-203 (DAC-sekvens ved digitalt skift):** fastlægges i område 4.
- **FR-204 (−6 dB):** Relæet er til på input 4 og 5.
- **FR-206 (persistens):** Input gemmes efter §9.8. Adressen fastlægges i område 7.
- **FR-207 (valg):**
  - Input vælges via touch, IR og UART (område 8).
  - Op/ned wrapper ikke og springer input 6 over, hvis phono-modulet mangler.
  - IR-kode 0 vælger input 10, men kun med DAC-modul.
- **FR-355 (AV):**
  - Input 3 og/eller 4 kan udpeges som AV.
  - På et AV-input får begge kanaler det faste relæ-indeks 66, uden balance, level match og
    digital gain.
  - Volumentrin ignoreres fra alle kilder, men mute er tilladt.

### 4.3 Volumen og level match

_Område 3._ [D333]-løsningen er `drv_volctl` og `svc_volume` (§8).

**Legacy: attenuator (kode læst).**

- **To I/O-expandere på I2C3:** U16 (`0x22`) styrer venstre kanal og U20 (`0x23`) højre
  (`Level_Control.c:10-11`).
  - Et relæ-indeks fra 0 til 84 slås op i tre tabeller med 85 indgange hver
    (`ui_globals.c:134-150`). Indeks 0 er det laveste niveau.
  - Tabelværdien skrives til register `0x84` (output 0 med autoincrement).

  [D333: én expander til begge kanaler og indeks 0–44.]
- **Make-before-break** (`Level_Control.c:125-165`) kører i tre faser. Faserne skiftes mellem
  L og R, og efter hver skrivning venter koden 2 ms (blokerende):
  1. Byte 1 = `(ny & 0xFC) | gammel`. Byte 2 og 3 = `ny | gammel`.
  2. Alle tre bytes = `ny | gammel`.
  3. Alle tre bytes = `ny`.

  IR-interruptet er slået fra under hele sekvensen (§9.12). [D333: to faser, 1 ms pr. fase.]
- **Relæ-indeks pr. kanal** (`Level_Control.c:45-73`), hvor `bal` er `leftBal` eller
  `rightBal` (`ui_globals.c:131-132`):
  - **Analogt input:** `curLvl + bal + inpSens[curInp]`, med loft ved 84.
  - **Digitalt input med digital gain:** `curLvl + 6 + bal`, med loft ved 84.
  - **Digitalt input uden digital gain:** `curLvl + bal`, uden loft (§9.10).
- **Green bias** følger `curLvl` (`MB_IOexp_U26_Control.c:365-389`) og hører til område 4.

**Legacy: niveau og grænser (kode læst).**

- **Niveau:** `curLvl` ligger mellem 0 og `maxLvl`. Ved tænding er `curLvl = startLvl`
  (`On_Off_Control.c:942`).
- **Grænser** (`Screen_Volume_Settings.c:57-98`):
  - Startniveauet ligger mellem 0 og 66, og maxniveauet mellem 20 og 84.
  - Startniveauet følger maxniveauet ned, og maxniveauet følger startniveauet op.
  - Ved indlæsning klemmes værdierne ind i grænserne (`eeProm_Functions.c:48-53`).
  - Defaults er start 0 og max 84 (`:400-401`).
  - Værdierne gemmes, når skærmen forlades (`Screen_Volume_Settings.c:178-183`).

  [D333: start 0–25, max 10–42.]
- **Touch:**
  - Ét trin ved tryk og derefter repeat efter 400 ms, med ét trin hver 120 ms.
  - Repeat stopper ved 0 eller max, efter 84 gentagelser, eller når touch har været uden
    opdatering i 250 ms eller er uden for knappen (`screen_Action.c:32-35`, `:197-293`).
  - Repeat kører i en `SYS_TIME`-callback (§9.1).
- **IR:** ét trin pr. kode (`IR_control.c:163-184`).
- **UART:** sætter niveauet, hvis værdien højst er max (`uart_control.c:341-344`, område 8).
- **Auto-mute ved niveau 0** (`Level_Control.c:75-95`): Er niveauet 0, og er inputtet ikke
  AV, så kaldes `muteOn()`. User-mute nulstilles, og mute-knappen deaktiveres.
- **Unmute ved volumentrin:** Vol-op fra 0 eller fra user-mute lukker relæet igen. Vol-ned
  gør det aldrig (`screen_Action.c:204-217`, `IR_control.c:166-182`,
  `Level_Control.c:96-123`).
- **User-mute:**
  - Touch og IR slår mute til og fra, men kun når niveauet er over 0 eller inputtet er AV
    (`screen_Action.c:525-544`, `IR_control.c:215-224`, `MB_IOexp_U26_Control.c:304-326`).
  - Mute åbner input-relæerne. Ved digital → digital bruges DAC-kanal-mute i stedet
    (`:259-271`).
  - Output-mute-bitten bruges kun i power-sekvenserne. [D333: niveau til 0, derefter
    relæ-mute.] 2.0 følger [D333]'s rækkefølge (§9.11).
- **Menu:**
  - Når menuen åbnes, mutes der (`app.c:107-116`).
  - Når menuen lukkes, skrives niveauet igen, og der unmutes, hvis niveauet er over 0 eller
    inputtet er AV, og der ikke er user-mute (`app.c:117-128`).

**Legacy: balance (kode læst).**

- Balance har 13 trin med midten i trin 6 (`Screen_Volume_Settings.c:9-21`, `:109-126`).
- Balance hæver den ene kanal med op til 6 relæ-trin. Den dæmper ikke den anden kanal
  (`ui_globals.c:131-132`).
- Balance gemmes sammen med start- og maxniveauet (`eeProm_Functions.c:316-317`).
- Adfærden bevares (§10.1).

[D333 har ingen balance (FR-300).]

**Legacy: level match (kode læst).**

- Hvert analogt input fra 1 til 6 har en offset på 0–8 relæ-trin, som vises som "+N dB"
  (`Screen_Input_Level_Match.c:171-182`, `:205`). Input 6 vises kun med phono-modul.
- Offsetten gemmes, når skærmen forlades (`:242-246`).
- Den lægges kun på analoge inputs, der ikke er AV (`Level_Control.c:67`, `:202-233`).
- Menuen er muted, så en ændring kan først høres, når menuen lukkes.

[D333: offset = `inpSens/2` i trin på 2 dB.]

**Krav til 2.0.** Mekanismen er [D333]'s `drv_volctl` og `svc_volume` (§8). Tabeller,
grænser og tider er Helios' egne.

- **FR-300 (attenuator):**
  - To expandere på I2C3: U16 (`0x22`) til venstre kanal og U20 (`0x23`) til højre.
  - Relæ-indeks 0–84.
  - Tabellerne overføres 1:1 fra legacy (`ui_globals.c:134-150`), og de skrives til
    register `0x84`.
- **FR-301 (make-before-break):**
  - Tre faser som i legacy, skiftevis L og R, med 2 ms efter hver skrivning.
  - Ventetiden er en tilstand og ikke en busy-wait (NFR-011).
  - Der er ingen IR-guard (§9.12).
- **FR-302 (relæ-indeks):** Indekset beregnes pr. kanal i `SvcVolume_SetContext`:
  - **Analogt input:** `niveau + balance + level match`.
  - **Digitalt input med digital gain:** `niveau + 6 + balance`.
  - **Digitalt input uden digital gain:** `niveau + balance`.
  - **AV:** fast 66.

  Alle veje har loft ved 84 (§9.10).
- **FR-303 (start- og maxniveau):**
  - Startniveauet ligger mellem 0 og 66, og maxniveauet mellem 20 og 84.
  - De følger hinanden som i legacy og klemmes ind i grænserne ved indlæsning.
  - Defaults er start 0 og max 84.
  - Værdierne gemmes, når skærmen forlades.
  - Ved tænding er niveauet lig startniveauet.
- **FR-304 (repeat):**
  - Touch giver ét trin ved tryk og derefter et trin hver 120 ms efter 400 ms.
  - Repeat stopper ved 0 eller max, efter 84 gentagelser, eller når touch har været uden
    opdatering i 250 ms eller er uden for knappen.
  - Repeat er tick-baseret i main-loopet (§9.1).
  - IR giver ét trin pr. kode.
- **FR-305 (mute og volumentrin):**
  - Vol-op fra 0 eller fra user-mute unmuter. Vol-ned unmuter aldrig.
  - Niveau 0 på et input, der ikke er AV, giver auto-mute. Det er ikke en user-mute, og
    mute-knappen deaktiveres.
- **FR-310 (user-mute):** Mute kan kun slås til og fra, når niveauet er over 0 eller
  inputtet er AV. Sekvensen følger §9.11.
- **FR-314 (menu):**
  - Når menuen åbnes, mutes der.
  - Når menuen lukkes, skrives niveauet igen, og der unmutes, hvis niveauet er over 0 eller
    inputtet er AV, og der ikke er user-mute.
- **FR-320 (balance, Helios-specifik):** 13 trin med midten i trin 6. Tabellerne `leftBal`
  og `rightBal` overføres 1:1, og adfærden bevares (§10.1). Balance gemmes sammen med
  start- og maxniveauet.
- **FR-860 (level match):**
  - Hvert analogt input fra 1 til 6 har en offset på 0–8 relæ-trin, som vises som "+N dB"
    (§11.4).
  - Input 6 vises kun med phono-modul.
  - Offsetten lægges kun på analoge inputs, der ikke er AV, og gemmes, når skærmen forlades.

### 4.6 DAC-modul og U26

_Område 4._ [D333]-løsningen er `drv_es9039`, `drv_ak4118`, `drv_u26`, `svc_dac` og
`app_audio_ctrl` (§8). Den er bænkbevist med Audio Precision (D333 #53, M9 DAC-paritet).
Forskelle fra [D333] står i klammer.

**Navne.** I Helios-koden er U26 mainboardets expander på 0x23. I [D333] hedder den
tilsvarende expander U21, og `drv_u26` er DAC-modulets expander på 0x20. 2.0 skal bruge ét
entydigt navn for hver (§11.5).

**Legacy: hardware (kode læst).**

- **DAC-modulet** sidder på I2C2:
  - DAC'en på 0x48.
  - DIR'en på 0x10, som kun bruges til at læse Fs.
  - DAC-modulets expander på 0x20 (`app.h:162-164`).

  Helios-koden navngiver ikke chippene. [D333]'s handoff kalder dem ES9039MSPRO og AK4118A,
  og registrene er de samme.
- **DAC-modulets expander:**
  - **Udgange** (register 0x06): bit 0 er I2S-mux (1 = DIR, 0 = USB), bit 1 er async/sync, og
    bit 2 er DSD-lavpas (`Dac_Control.c:96-115`, `:965-986`).
  - **Indgange** (16 bit fra register 0x00): USB-Fs i bit 0–3, lock i bit 8, DIR-int i bit 10,
    USB-opladning i bit 11, DSD i bit 12, USB tilsluttet i bit 13 og DAC-mute i bit 14
    (`Dac_Control.c:9-29`).
- **U26** (0x23, 3 bytes; `MB_IOexp_U26_Control.c:12-42`, `:152-167`):
  - **Byte 0:** input-relæer og output-mute (§4.2). Output-mute er aktiv lav (`:328-329`).
  - **Byte 1:** inputs. Bit 0 er phono-modul, og bit 1 er DAC-modul (`app.h:128-130`). Kun
    bit 2 har pull-up og interrupt (`:160-166`). Hvad bit 2 er forbundet til, står ikke i
    koden (§11.6).
  - **Byte 2:** bit 0 er MM/MC, bit 1 er −6 dB, bit 2 og 3 er LED for phono- og DAC-modul
    (aktiv lav), og bit 4–6 er green bias GB0–GB2.
- **Registerskrivninger med flere bytes:** U26-koden sætter autoincrement-bitten (0x80) i
  registeradressen (fx 0x84, 0x8C). Koden til DAC-modulets expander gør ikke. Den læser 2
  bytes fra 0x00 og skriver 2–4 bytes til 0x54 og 0x60 uden bitten (`Dac_Control.c:56-76`,
  `:990-1019`). Om chippen alligevel autoincrementer, står ikke i koden (§11.6). [D333 har
  kopieret init-tabellen 1:1.]

**Legacy: detektion og init (kode læst).**

- **Detektion:** Modulerne genkendes ved ON5 ud fra U26 byte 1, og modul-LED'erne sættes
  (`On_Off_Control.c:976-977`, `MB_IOexp_U26_Control.c:184-202`).
  - `getAmpStatus()` opdaterer flagene ved hvert senere interrupt, men initialiseringen
    køres ikke igen. Moduler kan altså ikke skiftes, mens enheden er tændt.
- **Init med DAC-modul** (`handleDacConfiguration`, `MB_IOexp_U26_Control.c:509-524`):
  1. `maxInp = 11`, modul-LED'en tændes, og DAC-modulets expander initialiseres.
  2. Async sættes, og koden venter 500 ms.
  3. `dacSetup()` (`Dac_Control.c:205-230`): GPIO, systemtilstand, TDM, volume-rate
     op og ned, PCM-filter, receiver (S/PDIF, derefter I2S), S/PDIF-valg og format (I2S-PCM).
     Derefter automute fra, mute-rampe fra, DAC tændt, master/slave-kick, I2S-mux til DIR,
     1 ms og automute til.
  4. `dirSetup()`: DIR register 1 = 0x5A.

  Hele sekvensen blokerer i ca. 800 ms, heraf 2 × 150 ms efter volume-rate
  (`Dac_Control.c:898`, `:907`). [D333: samme sekvens med watchdog-strobe under ventetiden.]
- **Phono-konfiguration:** `handlePhonoConfiguration()` (`MB_IOexp_U26_Control.c:486-507`)
  kaldes ikke, for kaldet er udkommenteret (`On_Off_Control.c:1045`). ON5 sætter
  `maxInp = 5` (`:978`), og kun DAC-grenen hæver den. Med phono-modul og uden DAC-modul er
  `maxInp` derfor 5, når inputtet valideres (`:1020`), så et gemt input 6 bliver til input 1.
  Det betyder også, at phono-tiden på 23 s i ON5 (`:1031`) aldrig bruges uden DAC-modul.
  `maxInp` sættes korrekt senere, når action-skærmen vises (`screen_Action.c:473-484`). Det er
  kode læst og ikke set på bænken.

**Legacy: valg af digitalt input (kode læst).** `setDigitalInput()` (`Dac_Control.c:926-962`)
blokerer:

1. DAC-kanalen mutes (register 86 = 0xFF), og koden venter 75 ms og derefter 100 ms.
2. **USB (input 7):** receiver = I2S, S/PDIF-valg = 0x04 og format = I2S-PCM. Der unmutes
   ikke her. Det gør lock-gaten.
3. **S/PDIF (input 8–11):** receiver = S/PDIF, register 89 = `(inp − 2) · 16 + 4`, format =
   S/PDIF, DIR register 3 = `0x48 + inp − 8`, register 89 igen og BCK-invert-toggle
   (2 × 5 ms). Derefter venter koden 30 ms og unmuter (75 ms). I alt ca. 290 ms.

   Unmute sker uden at se på `muteFlg`. Ved user-mute på et digitalt input mutes kun
   DAC-kanalen, og relæerne bliver lukket (`MB_IOexp_U26_Control.c:259-268`). Ved digital →
   digital springes det analoge mute over (§4.2). Skiftes der under user-mute til et
   S/PDIF-input, spiller det derfor, selvom mute vises (kode læst, ikke set på bænken).

[D333: samme registersekvens, ikke-blokerende og med retry (D333 §9.28).]

Ved et digitalt input lukker `setInputRelay()` desuden DAC-kanalen og åbner den igen, hver
gang holdet udløber, og ved volumenændringer fra niveau 0 (`MB_IOexp_U26_Control.c:412-433`,
`Level_Control.c:102`). Det koster 150 ms blokering hver gang. Her unmutes USB, når kablet
er tilsluttet, uden at se på lock.

**Legacy: status og lock-gate (kode læst).**

- **Poll:** `checkStatus()` kører, når `IO_EXP_INT` er lav eller `ampStatusChangeFlg` er
  sat (`MB_IOexp_U26_Control.c:203-212`):
  1. U26 byte 1 læses.
  2. Er der DAC-modul, og er inputtet digitalt, læses DAC-modulets expander.
  3. `handleDacStatusChange()` kaldes.
- **`handleDacStatusChange()`** (`Dac_Control.c:134-181`):
  - **USB-input:** Er kablet ikke tilsluttet, sættes receiveren til S/PDIF, og ellers til
    I2S. Ved DSD sættes DSD-lavpas efter settingen. Ved PCM slås lavpas fra, og PCM-filtret
    skrives. Der unmutes kun, når kablet er tilsluttet, der er lock, og der ikke er
    user-mute.
  - **S/PDIF-input:** Kun PCM-filtret skrives. Der er ingen lock-gate, og DAC'ens automute
    klarer stilheden.

  [D333: samme adfærd (D333 FR-404, FR-405 og §10).]

**Legacy: settings (kode læst).**

- **PCM-filter 1–7:** register 88 = 0xB8, 0xB9, 0xBA, 0xBC, 0xBD, 0xBE eller 0xBF. Er værdien
  ugyldig, bruges filter 4 (`Dac_Control.c:339-382`). Navnene er (`:507-536`):
  1. Minimum phase.
  2. Linear phase, apodizing.
  3. Linear phase, fast roll-off.
  4. Linear phase, slow roll-off.
  5. Minimum phase, fast roll-off.
  6. Minimum phase, slow roll-off.
  7. Minimum phase, slow roll-off, low dispersion.

  Filtret kan ikke vælges ved USB-DSD.
- **DSD-lavpas:** bit 2 på DAC-modulets expander. Det vises og kan vælges kun ved USB-DSD
  (`IR_control.c:382`, `Dac_Control.c:641-676`).
- **Digital gain:** Er det sat til "0 dB" (`digiGain = 1`), lægges 6 relæ-trin til. Er det
  sat til "−6 dB" (`digiGain = 0`), lægges intet til (`Level_Control.c:45-62`). Der skrives
  ikke til noget DAC-register. [D333: +3 trin ved 2 dB pr. trin, dvs. også 6 dB. Det bekræfter
  1 dB pr. trin på Helios (§11.4).]
- **Betjening:**
  - Settings ændres på skærmen Digital Setup og via IR.
  - Med IR går filtret rundt fra 7 til 1 (`IR_control.c:366-369`). På touch stopper det ved
    1 og 7 (`Screen_Digital_Setup.c:66-75`).
  - Settings gemmes, når skærmen forlades, og ved OFF (`:78`, `On_Off_Control.c:1107`) på
    EEPROM-adresse 0x07–0x0A (`eeProm_Functions.c:349-362`).
- **`dsdFilter`** (0x08) gemmes, men bruges ikke. `dacSetDSDFilter()` og begge knapper er
  tomme (`Dac_Control.c:686-689`, `Screen_Digital_Setup.c:63-64`).

**Legacy: Fs-visning (kode læst).**

- **USB:** Fs-indekset fra bit 0–3 på DAC-modulets expander slås op i `usbFsTabel`
  (32–384 kHz og DSD64–512). Er kablet ikke tilsluttet, vises "USB UNPLUGGED". Visningen
  holdes 350 ms efter en ændring (`screen_Action.c:1023-1056`, `ui_globals.c:78-93`).
- **S/PDIF:** Fs læses i DIR register 7, bit 4–7, af `DIR_FS_AcqTask`
  (`screen_Action.c:1142-1301`):
  - Ved lock-flanken resettes og initialiseres DIR'en igen.
  - Den første læsning sker efter 30 ms, og en ugyldig læsning prøves igen efter 20 ms, op
    til 10 gange.
  - Efter 3 fejlede runder initialiseres DIR'en igen, højst 3 gange pr. lock og med 600 ms
    imellem.
  - Under lock overvåges Fs hvert 200 ms.
  - Uden lock vises "NO SIGNAL".
- **Kun på action-skærmen:** Opgaven kører kun på action-skærmen, og højst hvert 200 ms
  (`screen_Action.c:1363-1367`). Re-init af DIR'en ved lock-flanken sker derfor ikke, hvis
  lock kommer, mens en anden skærm vises.
- **Tabellen er for kort:** `dirGetFs()` giver 0–15, men `dacFsTabel` har kun 15 indgange
  (`ui_globals.c:61-76`). Værdien 15 læser uden for tabellen.
- **Død kode:** `lockedButNoFs_Callback` (`screen_Action.c:320-324`) registreres ingen
  steder, så grenen i `updateActionScreen` (`:1415-1423`) kan ikke nås.

**Legacy: green bias (kode læst).** `U26_UpdateGreenBiasFromLevel()`
(`MB_IOexp_U26_Control.c:365-389`):

- Den kaldes ved hver `UpdateVolume()` (`Level_Control.c:40`) og ved ON4
  (`On_Off_Control.c:954`). ON1 sætter OFF-mønstret (`:886`).
- Den bruger `curLvl` og ikke det effektive relæ-indeks.
- Hvilken tærskeltabel der bruges, vælges på skærmen Green Bias (`Screen_GB_SETUP.c`):

  | Setting | LOW | MID | HIGH |
  |---|---|---|---|
  | 0 (`GB1`) | ≤ 26 | 27–46 | 47–84 |
  | 1 (`GB2`) | ≤ 38 | 39–58 | 59–84 |

- **Mønstre på GB2..GB0:** OFF = 001, MID = 010, LOW = 100 og HIGH = 000. Kommentarerne
  passer ikke til koden: HIGH kaldes "GB1+GB2" (`app.h:215`), failsafe-mønstret 001 kaldes
  "alt slukket" (`:359`), og filens hoved er i tvivl om polariteten (`:5-6`) (§11.6).

**Legacy: fejl-triggere (kode læst).** Der er ingen:

- U26 læses kun for moduldetektion. Fejlbits var tænkt i den gamle `getAmpStatus`, men de
  er udkommenteret (`MB_IOexp_U26_Control.c:678-679`).
- `errorCheckFlg` sættes og ryddes, men læses ingen steder (`On_Off_Control.c:974`,
  `:1110`).
- `saveErrorStatus()` og `getErrorStatus()` (`eeProm_Functions.c:371-386`) kaldes ingen
  steder.
- FR-106 har derfor ingen fejl-triggere fra legacy.

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
| TIM-xx | Inputskift: mute-hold kort / langt (D333 TIM-08: 200 / 2000 ms) | 200 / 2000 ms | `MB_IOexp_U26_Control.c:479` |
| TIM-xx | Inputskift: venten efter analog mute | 20 ms (blokerende) | `MB_IOexp_U26_Control.c:464` |
| TIM-xx | Make-before-break: venten pr. skrivning (D333 TIM-09: 1 ms pr. fase) | 2 ms × 6 skrivninger | `Level_Control.c:133-164` |
| TIM-xx | Volumen-repeat: første / gentagelse (D333 TIM-15: 400 / 120 ms) | 400 / 120 ms | `screen_Action.c:32-33` |
| TIM-xx | Volumen-repeat: stop uden touch-opdatering / maks. antal gentagelser | 250 ms / 84 | `screen_Action.c:34-35` |

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
| Volumen-attenuator med make-before-break | [D333] FR-300–306, `drv_volctl`, `svc_volume` | Mekanisme. Helios har to expandere (L/R), indeks 0–84, tre MBB-faser og balance (§4.3) | Bænkbevist (D333 #54, M9-paritet med Audio Precision) |
| Ikke-blokerende mute og inputskift med hold på 200/2000 ms | [D333] FR-202, FR-310–316, `svc_mute`, `svc_input`, `app_audio_ctrl` | Mekanisme. Helios' inputs, relæbits og −6 dB-inputs (§4.2) | Bænkbevist (D333 #54, #170, #174, #175) |
| AV-bypass og level match i volumenkonteksten | [D333] FR-302, FR-355, `SvcVolume_SetContext` | Mekanisme. Helios' AV-inputs 3/4 og indeks 66 | Bænkbevist (D333 #169) |

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
10. **(adfærd) Relæ-indekset har altid loft ved 84** (beslutning 2026-11-27).
    - **Legacy:** På et digitalt input uden digital gain er indekset `curLvl + bal`, uden
      loft (`Level_Control.c:60-61`). Ved niveau over 78 med balance til siden når det op
      til 90. Tabellerne har kun 85 indgange (`ui_globals.c:134-150`), så koden læser uden
      for tabellen og skriver tilfældige relæ-bytes (kode læst, ikke set på bænken).
    - **2.0:** Alle veje har loft ved 84, som den analoge vej og vejen med digital gain
      (`:52-55`, `:68-72`).
11. **(adfærd) Mute sætter niveauet til 0 før relæerne** (beslutning 2026-11-27).
    - **Legacy:** Mute åbner kun input-relæerne, og ved digitalt input mutes DAC-kanalen
      også. Volumenrelæerne bliver stående (`MB_IOexp_U26_Control.c:230-271`).
    - **2.0:** [D333]'s `svc_mute` (FR-311) genbruges med Helios' aktuatorer:
      - **Mute:** Niveauet sættes til 0, og derefter åbnes input-relæerne og mutes
        DAC-kanalen som i legacy.
      - **Unmute:** Relæerne lukkes, og derefter gendannes niveauet.
      - Output-mute-bitten (U26 bit 7) bruges stadig kun i power-sekvenserne.
    - **Begrundelse:** På [D333] beskytter rækkefølgen udgangsrelæerne i en integreret
      forstærker. Helios er en forforstærker, så formålet er ikke det samme. Rækkefølgen
      vælges alligevel, fordi den er bænkbevist på [D333], og Michael ikke ser nogen ulempe.
    - **Tider:** Ventetiderne efter niveau 0 og efter relæerne skal bænktestes på Helios.
      [D333] bruger 3 ms og 15 ms (TIM-06, TIM-07).
12. **Ingen IR-guard under make-before-break** (beslutning 2026-11-27), som [D333] §9.19.
    - **Legacy:** IR-interruptet er slået fra under hele volumensekvensen, ca. 12 ms
      (`Level_Control.c:126`, `:165`).
    - **2.0:** IR-ISR'en sætter kun et flag (NFR-010), så guarden beskytter ikke længere
      noget, og den kan koste IR-koder.
    - **Evidens:** [D333] #173 er verificeret på bænken: 18 s med tung IR-spam gav 111 rene
      MBB-par og ingen korruption.
    - **Bænktest på Helios:** Testen gentages med IR-spam under volumenskift. Den kan
      automatiseres med en Arduino som IR-kilde og UART som orakel.

---

## 10. Adfærd der SKAL bevares, selv om den kan ligne en fejl

_Udfyldes under område 2–9._

1. **Balance hæver den ene kanal** (beslutning 2026-11-27).
   - Balance lægger op til 6 relæ-trin til den ene kanal og dæmper ikke den anden
     (`ui_globals.c:131-132`).
   - Når balancen flyttes fra midten, stiger den samlede lydstyrke.
   - Fra niveau 79 og op æder loftet på 84 balancen. Ved niveau 84 er der ingen balance på
     analoge inputs, og efter §9.10 heller ikke på digitale.
   - Kurven er en parameter, som brugeren kan mærke, og den følger 1.0 (§1).
     [D333] har ingen balance.

---

## 11. Åbne spørgsmål

1. **Mappenavn** for 2.0 ved siden af `App/` (#1).
2. **Bit-identitet:** Er `v1.0` bit-identisk med det image, der er i marken? (#1)
3. **Kendte fejl og klager fra marken** er ikke samlet (#1). De er gode testcases.
4. **dB pr. relæ-trin på Helios** (område 3). Level match vises som "+N dB" pr. trin, og
   digital gain lægger 6 trin til. Det tyder på 1 dB pr. trin ([D333]: 2 dB), men det står
   ikke i koden. Tabellernes mapping fra bit til relæ og dB er heller ikke dokumenteret
   ([D333] har samme åbne punkt).
   - _Område 4:_ Digital gain er +6 trin på Helios og +3 trin ved 2 dB pr. trin på [D333].
     Begge giver 6 dB, og det støtter 1 dB pr. trin.
5. **Expander-navne** (område 4). U26 betyder mainboardets expander i Helios og DAC-modulets
   expander i [D333] (§4.6). Navnene i 2.0 vælges, før driverne skrives.
6. **Hardware-spørgsmål til DAC-modulet og U26** (område 4). Kan besvares ud fra
   diagrammet, eller ved at dumpe registrene over UART på bænken:
   - Hvad sidder på U26 byte 1 bit 2, som er den eneste pin med interrupt? Er det
     interruptet fra DAC-modulets expander?
   - Autoincrementer DAC-modulets expander uden bit 0x80? Hvis ikke, læses bit 8–14 af
     statusordet (lock, USB tilsluttet m.m.) forkert, og init-skrivningerne til 0x54 og 0x60
     rammer kun ét register.
   - Hvad er green bias' polaritet, og hvad er HIGH-mønstret (000)?

---

*Dokumentet vedligeholdes efter samme meta-regel som [D333]: huller opdaget under
implementeringen rettes her, før koden skrives.*
