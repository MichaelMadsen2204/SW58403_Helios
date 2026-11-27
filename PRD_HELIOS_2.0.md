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
  - **Kildens version (beslutning 2026-11-27):** D333 læses fra `origin/main` efter
    `git fetch` (`git show origin/main:<fil>`), ikke fra det lokale checkout, som kan være
    bagud. Område 1–5 er læst fra et checkout af 2026-10-28, som var 312 commits bagud for
    `origin/main` (2026-11-17). Deres D333-referencer (FR-, TIM- og §9-numre samt bænkstatus)
    er tjekket mod `origin/main` (`fe1787d`) 2026-11-27. Ingen numre er flyttet. NACK-reglen i
    §9.19 og bænkstatus i §8 er rettet.
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
| GPIO ind (power) | `ON_OFF_BUTTON` RJ15 (CN, høj = trykket), `LINK_12V` RB4 (aktiv lav), `IR_RC5` RH3 (CN; kommentaren i `On_Off_Control.c:1162` siger fejlagtigt RH11), `AC_RESULT` RE8 (1 = `VoltageLow`, 0 = `VoltageHigh`), `AC_RESET` RC4 (høj = venstre forsyning til stede), `ACTIVATE_BOOTLOADER` (CN) (`plib_gpio.h`, `ac_check.h:39-49`) |
| GPIO ud (IR) | `IR_SOURCE` RH11 vælger IR-modtager: 1 = front, 0 = bag (`plib_gpio.h:190-197`, `app.h:154-155`) |
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
| `VolRepeat_Callback`, `VolInitialDelay_Callback` | Ændrer `curLvl` og registrerer nye timere; selve I²C-skrivningen sker i main-loopet, i skærmens opdateringsfunktion (`updateActionScreen`, `screen_Action.c:1394-1404`, og `updateSimpleViewScreen`, `Screen_SimpleView.c:22-26`), når `curLvl` er ændret | `screen_Action.c:197-273` |

Øvrige callbacks sætter kun flag (`IR_control.c:66-77`, `ac_check.c:42-50`,
`On_Off_Control.c:1261-1265`, `Level_Control.c:15-18`, `eeProm_Functions.c:71-81`).

**Krav til 2.0:**

- **NFR-010:** Bare-metal superloop som legacy. Al applikationslogik kører som tick-baserede
  state machines fra main-loopet. ISR'er og `SYS_TIME`-callbacks sætter kun flag eller
  tidsstempler ([CONV] §3–4). De kalder aldrig Legato, I²C, backlight, `printf`, delays eller
  `SYS_TIME`-API'er, og de skriver aldrig til en tilstandsvariabel, som main-loopet også
  skriver. Undtagelse: IR-ISR'en sampler en hel RC5-frame (§9.20). Den skriver kun
  driverens egen kode-buffer.
- **NFR-011:** Ingen blokerende delays i normal drift. Ventetider er state-machine-tilstande
  med sammenligning af tidsstempler. Undtagelser markeres `// CONVENTION-EXCEPTION:` og står
  her. Område 2: sleep-kaldet og UART-drænet før sleep (§4.1). Område 4: DAC-init i ON5
  (FR-400). Område 5: IR-bit-sampling i CN-ISR'en (§9.20), som [D333].
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
  - **Touch-hooks:** `le_gen_harmony.c` er urørt. Touch-hændelser til appen (fx volumen-repeat)
    går via en egen `SYS_INP`-lytter, som [D333] `touch_bridge.c` registrerer med
    `SYS_INP_AddListener` fra `APP_Initialize()`. `SYS_INP_MAX_LISTENERS` er 2, og Legato
    bruger den ene, så en tredje lytter kræver, at konstanten hæves via MCC.
  - **Eneste undtagelse:** Touch-genopretningen i `drv_touch_controller.c`
    `DRV_TOUCH_STATE_ERROR` som [D333] #60 og #103. Den skal genindsættes efter hver
    regenerering, der rører touch-driveren, efter en fast procedure ([D333]
    `README_REBUILD.md`). Diffen tjekkes efter hver regenerering (MCC-001). Se §9.29.
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
  - **Skærmtjekket ligger i GUI-funktionen selv**, ikke hos kalderen, og et widget skrives kun,
    når værdien ændres.
  - **Legacy (område 6):** `updateSimpleViewScreen` skriver mute-krydset i hvert tik uden eget
    skærmtjek (`Screen_SimpleView.c:28-31`). Det er sikkert, fordi kalderen gater
    (`app.c:205`), men kontrakten er skrøbelig.
- **NFR-021:** Den kapacitet, der gives til `leFixedString_Constructor`, afledes altid af
  bufferen (`sizeof(buf) / sizeof(buf[0])`) og skrives aldrig som et tal.
  - **Legacy:** Kapaciteten er 16, men bufferne har kun 9 elementer
    (`Screen_Input_Level_Match.c:13-18`, `:203-233`) og 8 elementer
    (`Screen_Volume_Settings.c:23-24`, `:146`, `:162`).
  - Der sker intet overløb i praksis, for den længste tekst er "+8 dB". Men den grænse,
    som Legato håndhæver, er forkert.
  - **Område 6:** Samme fejl i `Screen_SimpleView.c` med 8 elementer (`:10`/`:91`) og 9
    elementer (`:12`/`:160`), i `Screen_Qwerty_Keypad.c` med 9 elementer (`:29-30`/`:272-273`) og
    i `legatoCharBuffer` med 8 elementer (`ui_globals.c:24`, brugt i `screen_Action.c:758` og
    `Screen_SimpleView.c:101`). Kapaciteten er 16 alle steder.
    - `setFromCStr` klipper længden til kapaciteten og skriver ingen terminator
      (`legato_fixedstring.c:193-205`). Et inputnavn er højst 8 tegn (`inpNames[12][9]`), og
      display-modeteksterne er højst 8 tegn ("AUTO OFF", `ui_globals.c:54-59`), så der sker
      intet overløb. Det eneste overløb kommer via
      format-fejlen i §9.28.
    - Inputnavne, Fs og FW (16 mod 16) og SN (8 mod 6) er i orden.
- **GUI-002 (fonte til dynamisk tekst):** En font, der bruges til en dynamisk tekst, har et
  tegninterval i Composer, som dækker alt, hvad kilden kan give. Kildens tegnsæt og fontens
  intervaller står ved siden af hinanden i koden eller i testen.
  - **Legacy (kode læst):** Fontindekset er læst fra `stringTable_data`
    (`le_gen_stringtable.c`) og tegnområderne fra `le_gen_fonts.c`. Tastaturet er
    Windows-1252 (Å = 0xC5, Æ = 0xC6, Ø = 0xD8) med ASCII-symboler
    (`Screen_Qwerty_Keypad.c:31-36`).

    | Tekst | Font | Tegnområder |
    |---|---|---|
    | Inputnavne: action (`Inp1–11Name`), level match, tastaturets redigeringsfelt | `Avenir18` | 0x20–0x7E, 0xC5–0xD8 |
    | Inputnavn på simple view | `Avenir64` | 0x20–0x7E, 0xC5–0xD8 |
    | Display-mode, start- og maksniveau, PCM-filter | `avenir48` | 0x20, 0x23–0x5A |

  - Alle kilder er dækket. `avenir48` mangler Æ, Ø, Å og `! ' ^ _ ~`, men viser kun store
    bogstaver, cifre og `%`.
- **GUI-001 (vedvarende valg-indikation):** _Helios' vælgerskærme er ikke undersøgt endnu
  (område 6)._

---

## 4. Funktionelle krav

_Udfyldes område for område. Rækkefølge for gennemgangen:_

| Område | Afsnit | Legacy-filer | Status |
|---|---|---|---|
| 1 | §3.2 Eksekveringsmodel | `main.c`, `app.c`, `app.h`, `tasks.c` | Gennemgået 2026-11-27 |
| 2 | §4.1 Power | `On_Off_Control.c`, `ac_check.c`, `voltageSetting.c`, `ui_voltage_Error.c` | Gennemgået 2026-11-27 |
| 3 | §4.2–4.3 Input, level, level match | `Level_Control.c`, `Screen_Input_Level_Match.c`, `Screen_Volume_Settings.c` | Gennemgået 2026-11-27 |
| 4 | §4.6 DAC og U26 | `Dac_Control.c`, `MB_IOexp_U26_Control.c`, `Screen_Digital_Setup.c` | Gennemgået 2026-11-27 |
| 5 | §4.9 IR | `IR_control.c`, `Screen_IR_Source_Setup.c` | Gennemgået 2026-11-27 |
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
- IR under opstart: kun sluk (12/124) fra ON4 (§9.22). Persistens under opstart fastlægges i
  område 7.
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

  Der er ingen fejl-triggere fra DAC-modulet eller U26 (§4.6).
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
- **FR-203 (DAC-sekvens ved digitalt skift):** står i §4.6.
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
  - Volumensekvensen slår ikke IR fra. En bus-guard udsætter i stedet IR-dekodningen under
    I²C (§9.12).
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
  - +/− på `volSettingsScreen` giver tryk-hold-gentagelse som FR-304 (§9.34).
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

**Krav til 2.0.** Mekanismen er [D333]'s `drv_es9039`, `drv_ak4118`, `drv_u26`, `svc_dac` og
`app_audio_ctrl` (§8). Registersekvenserne er legacy's, som [D333] har kopieret 1:1. Inputs,
tabeller og tider er Helios' egne.

- **FR-203 (DAC-sekvens ved digitalt skift):** Sekvensen er en del af transition-mute'en
  (FR-202) og blokerer aldrig (NFR-011).
  1. DAC-kanalen mutes (register 86 = 0xFF), og ventetiden på 75 + 100 ms er tilstande.
  2. **USB (input 7):** receiver = I2S, S/PDIF-valg = 0x04 og format = I2S-PCM.
  3. **S/PDIF (input 8–11):** receiver = S/PDIF, register 89 = `(inp − 2) · 16 + 4`,
     format = S/PDIF, DIR register 3 = `0x48 + inp − 8`, register 89 igen og
     BCK-invert-toggle (2 × 5 ms) og 30 ms.
  4. Kanalen efterlades mutet. Den unmutes kun i `svc_mute` (§9.13, FR-404).

  En fejlet skrivning prøves igen efter §9.19.
- **FR-400 (init):** Kun når DAC-modulet er detekteret i ON5 (FR-407), i samme rækkefølge som
  legacy (§4.6):
  1. DAC-modulets expander initialiseres, og async sættes.
  2. Der ventes 500 ms.
  3. `dacSetup()`-sekvensen, med automute fra under init og til til sidst.
  4. `dirSetup()`: DIR register 1 = 0x5A.

  Init blokerer i ca. 800 ms med watchdog-strobe under ventetiden, som [D333]. Det er en
  undtagelse fra NFR-011.
- **FR-401 (PCM-filter):**
  - Filter 1–7 skrives til register 88 efter tabellen i §4.6. En ugyldig værdi giver
    filter 4.
  - Filtret gælder USB-PCM og S/PDIF og kan ikke vælges ved USB-DSD.
  - Det vælges på skærmen Digital Setup og via IR (§10.2).
  - Det gemmes, når skærmen forlades. Adressen fastlægges i område 7.
- **FR-402 (DSD-lavpas og digital gain):**
  - DSD-lavpas er bit 2 i DAC-modulets expander. Det vises og kan vælges kun ved USB-DSD.
  - Digital gain er FR-302 (+6 relæ-trin). Der skrives ikke til noget DAC-register.
  - Begge vælges på skærmen og via IR og gemmes som FR-401.
- **FR-403 (status):**
  - Statusordet (16 bit fra register 0x00 i DAC-modulets expander) har bittene fra §4.6.
  - Det læses ved `IO_EXP_INT` og periodisk, når et digitalt input er valgt, som [D333]
    FR-403.
  - Læsningen afhænger af autoincrement (§11.6).
- **FR-404 (USB-lock-gate, ufravigelig):** På USB-inputtet unmutes DAC-kanalen kun, når kablet
  er tilsluttet, der er lock, holdet er udløbet, og der ikke er user-mute (§9.13). Gaten
  evalueres ved hver statusændring. S/PDIF gates ikke på lock. Det klarer DAC'ens automute
  (§4.6).
- **FR-405 (USB tilsluttes eller fjernes):** På USB-inputtet skiftes receiveren automatisk
  mellem I2S og S/PDIF. DSD-lavpas eller PCM-filter skrives igen efter den aktuelle tilstand.
- **FR-406 (Fs-visning):**
  - **USB:** Fs-indekset fra bit 0–3 slås op i USB-tabellen (32–384 kHz og DSD64–512). Er
    kablet ikke tilsluttet, vises "USB UNPLUGGED".
  - **S/PDIF:** Fs kommer fra Helios' tilstandsmaskine i `svc_dac` med tiderne fra legacy
    (§9.15). Uden lock vises "NO SIGNAL".
  - Visningen holdes 350 ms efter en ændring.
  - En værdi uden en indgang i tabellen vises som "NA" (§9.16).
  - Mens et skift venter på retry (§9.19), vises "NO SIGNAL".
- **FR-407 (moduldetektion):**
  - Phono- og DAC-modul genkendes i ON5 ud fra U26 byte 1, bit 0 og bit 1.
  - Modul-LED'erne (byte 2, bit 2 og 3, aktiv lav) følger detektionen.
  - Moduler kan ikke skiftes, mens enheden er tændt, som i legacy.
  - `maxInp` afledes af begge moduler (§9.14).
- **FR-410 (green bias, Helios-specifik):**
  - Trinnet skrives til U26 byte 2, bit 4–6, med mønstrene fra §4.6 (polaritet: §11.6).
  - Det beregnes ud fra `curLvl` (§10.3), og på et AV-input ud fra 66 (§9.18).
  - Tærskeltabellen vælges med settingen 0 eller 1 på skærmen Green Bias. Adressen
    fastlægges i område 7.
  - Trinnet opdateres ved hver volumenændring og i ON4. ON1 sætter OFF-mønstret.

### 4.9 IR-fjernbetjening

_Område 5._ [D333]-løsningen er `drv_ir_rc5`, `app_ir` og `gui_remote_view` (§8). Den er
bænkbevist (D333 #56, #162, #280 del B), men ikke i drift i marken. Forskelle fra [D333]
står i klammer.

**Legacy: hardware og dekoder (kode læst).**

- **Pins:** `IR_RC5` er RH3 med CN-interrupt (`plib_gpio.h:215-219`). Signalet er
  TSOP-demoduleret: hvile = 1, burst = 0 (`IR_control.c:14-17`). `IR_SOURCE` RH11 vælger
  modtager (se IR-kilde nedenfor).
- **Interrupt:** CN-handleren tjekker, at linjen er lav, og sætter kun et flag:
  `s_irRxPending` i ON og `s_irWakePending` i standby (`IR_control.c:66-77`). Den kører på
  alle flanker (CN i mismatch-tilstand, `plib_gpio.c:104`), også under dekodningen.
- **Dekodning i main-loopet:** `ServiceIr()` kaldes først i `APP_Tasks` (`app.c:163`,
  `IR_control.c:79-89`) og dekoder blokerende (`irDecodeRawCode`, `IR_control.c:448-492`):
  1. Den venter på lav linje i op til 40 000 × 1 µs (`RC5_TIMEOUT_US`).
  2. Den antager, at den står på den faldende flanke midt i S1, og venter 1333 µs
     (889 + 444).
  3. Den læser 13 bits (S2…C0) med to samples pr. bit med 889 µs imellem.
  4. Et ugyldigt Manchester-par giver yderligere 25 ms blokering og en kasseret frame
     (`:486`).

  Selve læsningen tager ca. 24 ms. Hvor lang tid der går fra flanken til `ServiceIr()`,
  afhænger af main-loopet. Koden kompenserer ikke for den latens (udledt, ikke målt).
  [D333: sampling i CN-ISR'en på faldende flanke med interrupts slået fra, 448 µs offset og
  910 µs halvbit (D333 TIM-23), `CONVENTION-EXCEPTION`.]
- **Frame-felter** (`irReceive`, `IR_control.c:853-874`): bit 13 = S1, bit 12 = S2 (felt),
  bit 11 = toggle, bit 10–6 = system, bit 5–0 = kommando. Felt = 0 giver kommando + 64
  (RC5X). [D333 afkoder RC5X, men kasserer kommandoer over 63.]
- **System:** Kun system 16 behandles (`:689`, `:723`).
- **IR under volumenskrivning:** CN-interruptet er slået fra under make-before-break
  (`Level_Control.c:126`, `:165`). I 2.0 udsætter en bus-guard i stedet IR-dekodningen under
  I²C (§9.12).

**Legacy: toggle og gentagelse (kode læst; `IR_control.c:682-808`).**

- **Nyt tryk:** En kommando behandles kun, når togglebitten er skiftet. Undtagelser:
  - volumen op og ned (altid),
  - `com_power_on` i standby og `com_power_off` i ON,
  - `com_on_off` i standby.
- **Hold på volumen:**
  1. Første frame giver ét trin.
  2. Næste frame med samme kommando og samme toggle blokerer main-loopet i 200 ms
     (`CORETIMER_DelayMs(200)`, `:795`) og giver intet trin.
  3. Derefter giver hver modtaget frame ét trin, indtil togglebitten skifter.

  RC5 gentager en frame hver ca. 114 ms (RC5-standarden, ikke Helios-koden). Frames, der
  ankommer under blokeringen, tabes (udledt). [D333: 200 ms fra sidste accept, ikke-blokerende
  (D333 FR-702).]
- **Død kode:** `ignoreToggleFlg` sættes aldrig til 1, og `ignoreToggleCnt` tælles aldrig op,
  så `ignoreToggleCnt <= 100` er altid sand (`:21-23`, `:685`, `:700`). `irOneStepVol`
  sættes, men læses aldrig.

**Legacy: kommandoer (kode læst; `app.h:101-113`, `IR_control.c:115-426`, `:811-839`).**

| Kode | Kommando | Betingelse og virkning |
|---|---|---|
| 0 | Input 10 | Kun med DAC-modul (`maxInp == 11`, `:151-154`) |
| 1–11 | Direkte inputvalg | `1 ≤ kode ≤ maxInp`. Kode 6 kun med phono, men `irInputChangeFlg` sættes også uden (`:146-150`) |
| 12 | `com_on_off` | ON: sluk (`RequestPowerOff_FromIR`). Standby: tænd (`KeyOnOff`) |
| 13 | Mute | Kun når `curLvl > 0` eller AV-input. Sætter `muteToggleFlg`, som `irToggleMute()` udfører i main-loopet (`MB_IOexp_U26_Control.c:304-315`) |
| 15 | Display | Se Display-kommandoen nedenfor |
| 16 / 17 | Volumen op / ned | Ét trin. Ikke under input-mute og ikke på AV. Op ved niveau 0 eller mute rydder `skipUnmuteFlg`, ned sætter det (§4.3) |
| 21 | Monitor | Defineret, men ingen handling (`default`) |
| 32 / 33 | Input op / ned | Ingen wrap. Input 6 springes over uden phono |
| 36 | Gain | Kun på digitalt input (`curInp ≥ 7`). Skifter `digiGain` og kalder `dacSetGain()` |
| 48 | DSD-LP | Kun input 7 med DSD. Skifter `dsdLpFilter` (`reqApplyDsdLp`) |
| 50 | Filter | Input 7 uden DSD eller input ≥ 8. `pcmFilter` cykler 1–7 (`reqApplyPcmFilter`) |
| 123 | Diskret tænd (RC5X) | Kun i standby |
| 124 | Diskret sluk (RC5X) | Kun i ON |

- **Remote view:** Kommandoerne 0–11, 13, 16/17 og 32/33 ignoreres, mens
  `remoteViewDelayFlg` er sat, dvs. mens et IR-overlay vises.
- **Menu:** I menuen behandles kun 12 og 124 (`:716-730`).
- **Efter en accepteret kommando** genstartes dim-timeren (T_DIM) og på action-skærmen også
  T_ACTIONVIEW, og intensiteten gendannes (`IrRefreshDisplayActivityForCurrentScreen`,
  `:513-541`). Det sker på action, simple view og de fire overlay-skærme.

**Legacy: overlays fra simple view (kode læst; `IR_control.c:292-426`).**

- **Filter, DSD-LP og Gain:** På simple view viser første tryk kun overlayet
  (`filterSimpleView`, `dsdLpSimpleView`, `dacGainSimpleView`) i 3 s og ændrer intet. Et tryk
  på et andet skærmbillede, også overlayet selv, ændrer værdien. Efter 3 s vender
  `remoteViewDelay_Callback` tilbage til simple view, hvis den er slået til (`:91-97`).
  Timeren genstartes ikke af flere tryk.
- **Eksklusivt overlay:** Står et af de tre overlays fremme, ignoreres de to andre
  overlay-kommandoer (`:655-680`, `:742-746`).
- **Display (15):** Udenfor menu:
  - På action eller simple view vises `displaySimpleView` i 3 s. Derefter vender
    `remoteViewDispDelay_Callback` tilbage til forrige skærm og sætter `saveDisplayFlg`
    (`:99-113`).
  - På `displaySimpleView` cykler `dispMode` 0–5, og 3 s-timeren genstartes. Widgetten
    skrives direkte fra main-loopet (`:343-344`).
- **UI-skift** sker via `reqUiAction` og `handleUIRequests` (`app.c:73-142`).
  Callbacken `remoteViewDispDelay_Callback` kalder `SYS_TIME_TimerDestroy` i ISR (§3.2).

**Legacy: display slukket eller dæmpet (kode læst; `IR_control.c:559-604`, `:734-788`).**

- Tilstanden afledes af `dispSleepActiveFlg` og `dispMode` (`modeDim`, `modeOff`).
  `dispSleepActiveFlg` sættes, når dim-timeren udløber (`screen_Action.c:356`).
- **Slukket display:**
  - 12 og 124 udføres uden at tænde baglyset.
  - Filter, DSD-LP og Gain på en simple-lignende skærm behandles normalt, så på simple view
    vises overlayet. Displayet tændes forsinket via skærmskiftet (`irDeferredDisplayOnFlg`,
    `app.c:79-106`).
  - Alle andre kommandoer tænder kun displayet og sluges. En wake-guard sluger derefter alle
    frames med samme toggle (hold). Først et nyt tryk udføres.
- **Dæmpet display:** Displayet tændes, og kommandoen udføres.
- **Død kode:** `isImmediateWhenDisplayOff`, `isDeferredUiWakeCommand`, `isVolumeCommand`,
  `irActionScreenDisplayTiming` og `irSimpleViewScreenDisplayTiming` kaldes ingen steder.

**Legacy: IR i standby og under opstart (kode læst).**

- **CN-interruptet** slås til i ON4 (`On_Off_Control.c:945`) og fra i OFF-sekvensen (`:1140`).
  Efter en manuel sluk med aktivt 12V-link slås det til igen før IDLE, så IR kan vække (`:1165`).
- **Opvågning:** Er IR-linjen lav, poller `wakeUp()` IR i op til 500 ms efter `KeyOnOff`
  (`PollIrForOn`, `IR_control.c:42-64`, `On_Off_Control.c:711-738`).
  - `KeyOnOff` sættes af 12 og 123.
  - Uden gyldig kode går enheden i sleep igen.
  - `wakeUp()` kaldes også fra INT0-ISR'en (§3.2).
- **Andre kommandoer i standby:** `PollIrForOn` sender hver frame gennem hele
  `handleIrCommand`. Volumen og inputvalg ændrer derfor `curLvl` og `curInp` i standby
  (udledt). ON4 sætter `curLvl = startLvl` (§4.1). Om `curInp` overskrives, tjekkes i område 7.
- **Under opstart:** `wakeUpFlg` ryddes i ON4 (`On_Off_Control.c:946`), og derefter blokerer
  `handleIrCommand` kun i menuen (`:716-721`). IR-kommandoer behandles derfor i ON5–ON7
  (udledt). [D333 ignorerer IR under hele tænd-sekvensen (D333 FR-102, FR-703).]

**Legacy: IR-kilde (Helios-specifik; kode læst).**

- `IR_SOURCE` sættes høj i `initAmp`, derefter til EEPROM-værdien fra adresse 0x05 uden
  validering (`On_Off_Control.c:558`, `:625-628`, `eeProm_Functions.c:213`). Enhver værdi
  ≠ 0 giver front.
- Skærmen IR Source har to knapper, front og bag. Valget lægges straks ud på pinden, men
  gemmes først i EEPROM, når der trykkes "tilbage til menu" (`Screen_IR_Source_Setup.c:13-33`,
  `eeProm_Functions.c:333-336`).
- Restore Settings sætter pinden efter `irSource` (`Screen_Restore_Settings.c:44-47`).
  Standardværdien fastlægges i område 7.
- [D333 FR-705 har samme skærm og samme kodning, men gemmer valget straks (§9.27).]

**Krav til 2.0.** Mekanismen er [D333]'s `drv_ir_rc5`, `app_ir` og `gui_remote_view` (§8).
Numrene følger [D333] FR-700–705. FR-706 og FR-707 er Helios-specifikke.

- **FR-700 (dekoder):**
  - RC5 samples i CN-ISR'en på faldende flanke som [D333] (§9.20), med
    `CONVENTION-EXCEPTION` (NFR-010, NFR-011).
  - En bus-guard udsætter dekodningen under I²C (§9.12).
  - Kun system 16 accepteres.
  - RC5X-feltbitten giver kommandoerne 64–127, og de sendes videre.
  - En ugyldig frame kasseres uden ventetid (§9.25).
  - Tiderne bevises på Helios' modtager (§5, §9.20).
- **FR-701 (kommandoer):**
  - Kommandotabellen i §4.9 med betingelserne fra legacy. Undtagelsen er §9.23: et
    inputvalg, der intet ændrer, gør intet.
  - Kode 21 og ukendte koder ignoreres (§9.26).
  - Mute virker kun ved `curLvl > 0` eller på AV-input.
  - PCM-filtret går fra 7 til 1 (§10.2).
- **FR-702 (toggle og hold):**
  - Et nyt tryk kræver, at togglebitten skifter.
  - Hold accepteres kun for volumen op og ned, efter [D333] FR-702 med 200 ms (§9.25).
  - **Undtagelse (Helios):** I standby accepteres 12 og 123 uanset toggle, og i ON
    accepteres 124 uanset toggle, som i legacy. 12 i ON kræver nyt tryk.
- **FR-703 (gating):**
  - **Standby:** kun 12 og 123 (§9.21).
  - **Opstart:** kun 12 og 124 fra ON4 (§9.22).
  - **Menu:** kun 12 og 124.
  - **Mens et IR-overlay vises:** inputvalg, volumen, mute og input op/ned ignoreres.
  - **Eksklusivt overlay:** Står Filter-, DSD-LP- eller Gain-overlayet fremme, ignoreres de
    to andre overlay-kommandoer.
- **FR-704 (overlays):**
  - På simple view viser første tryk på Filter, DSD-LP eller Gain kun overlayet i 3 s.
    Tryk på overlayet udfører handlingen og genstarter timeren (§9.24). Efter timeout vises
    simple view igen.
  - På action-skærmen udføres handlingen direkte.
  - **Display (15):** Fra action eller simple view vises `displaySimpleView` i 3 s med
    retur til forrige skærm. På `displaySimpleView` cykler `dispMode` 0–5, og timeren
    genstartes. `dispMode` gemmes ved retur (område 7).
- **FR-705 (IR-kilde):**
  - `IR_SOURCE` RH11: 1 = front, 0 = bag, standardværdi front.
  - Sættes fra EEPROM 0x05 ved opstart og ved Restore Settings.
  - Valget på skærmen IR Source lægges straks ud på pinden og gemmes straks (§9.27).
- **FR-706 (power og opvågning, Helios-specifik):**
  - 12 slukker i ON og tænder i standby. 123 tænder i standby, og 124 slukker i ON
    (FR-106 b).
  - I standby søges tænd-koden inden for noise-guarden (FR-120). Der er intet separat
    IR-vindue (§9.25).
  - CN-interruptet på `IR_RC5` er slået til i ON og i IDLE efter en manuel sluk med aktivt
    12V-link (FR-120).
- **FR-707 (display slukket eller dæmpet, Helios-specifik):** Legacy-adfærden i §4.9
  bevares.
  - **Slukket display:**
    - 12 og 124 udføres uden at tænde baglyset.
    - Filter, DSD-LP og Gain på en simple-lignende skærm behandles, og displayet tændes
      ved skærmskiftet.
    - Alle andre kommandoer tænder kun displayet. Frames med samme toggle sluges, indtil et
      nyt tryk kommer.
  - **Dæmpet display:** Displayet tændes, og kommandoen udføres.
  - **Efter en accepteret kommando** genstartes T_DIM og på action-skærmen T_ACTIONVIEW.
  - **Auto Standby:** Nedtællingen nulstilles af enhver gyldig frame, også én, der kun tænder et
    slukket display, som [D333] FR-107. Frames, der sluges, fordi de har samme toggle, nulstiller
    ikke (beslutning 2026-11-27).

**UART-orakel:** Hver accepteret IR-kommando skal give en hændelseslinje på UART'en, så
bænktesten i §9.20 kan automatiseres (HIL-003). Formatet fastlægges i område 8.

### 4.10 GUI

_Område 6._ Auto Standby-overlay og menupunkt (FR-815, FR-816).

**Beslutninger (2026-11-27, Michael):**

- **`SN_SET` udgår.** Skærmen vises ingen steder i 1.0 (`legato_showScreen(screenID_SN_SET)`
  findes ikke). Serienummeret bruges kun via UART (`uart_control.c:431`, `:465`, område 8).
- **`errorDisplay` bliver SYSTEM ERROR-skærm.** Skærmen vises heller ingen steder i 1.0. Helios er
  en forforstærker uden fejlbit fra et effekttrin, så [D333] FR-515 gælder ikke. I stedet
  genbruges skærmen til [D333] FR-530 (SYSTEM ERROR med fejlkoder, `app_health` +
  `gui_system_error`, §9.41 i [D333] på `origin/main`), fx til I²C-busfejl. Kodetabellen til
  Helios står i FR-830.

**Legacy-adfærd uden krav endnu (kode læst).** Kravene skrives sammen med [D333] FR-850/§9.43
(MM/MC og ugyldig `pickupSel`) og FR-861/§9.42 (AV gråtonet i level match):

- **Pickup MM/MC:** Ved et skift sættes niveauet til 0, valget gemmes, og U26 sættes. Så vises
  en progressbar, der tæller til 100 med ét trin hver 250 ms, i alt 25 s
  (`Screen_Pickup_Selection.c:49-74`).
- **AV-skærmen:** Valgmulighederne er ingen, input 3 og input 4 som toggles. Valget gemmes på
  `OnHide` (`Screen_AV_Setup.c`).

**Legacy: skærmkatalog (kode læst; `le_gen_init.h:40-62`).** Der er 23 skærme:

| Gruppe | Skærme | Hvem viser den |
|---|---|---|
| Opstart | `splashScreen` | `le_gen_init.c:39`. Efter ON vises simple view eller action (`On_Off_Control.c:1072`, `:1081`) |
| Drift | `actionScreen`, `simpleViewScreen` | Skiftet sker ved timeout og touch (se nedenfor) |
| IR-overlays | `filterSimpleView`, `dsdLpSimpleView`, `dacGainSimpleView`, `displaySimpleView` | `handleUIRequests` (`app.c:75-106`), §4.9 |
| Menu | `mainMenuScreen` og 10 undermenuer: `volSettingsScreen`, `displayIntensityScreen`, `irSourceScreen`, `digitalSetupScreen`, `inpLvlMatchScreen`, `renameInputsScreen` (→ `qwertyScreen`), `avInputScreen`, `restoreSettingScreen`, `pickupSelectScreen`, `greenBiasScreen` | `Screen_Main_Menu.c:24-61`. Alle undermenuer vender tilbage til hovedmenuen |
| Fejl | `leftPowerMissingScreen`, `wrongAcVoltageScreen` | `showAcError` (`app.c:51-65`), `ac_check.c:140-143`, område 1 |
| Ubrugt | `SN_SET`, `errorDisplay` | Ingen. Se beslutningerne ovenfor |

**Legacy: drift-skærmene (kode læst).**

- **Action → simple view:** Når `T_ACTIONVIEW` (6 s) udløber, skifter skærmen, hvis simple view
  er slået til og menuen ikke er åben (`screen_Action.c:326-334`). Callbacken kalder
  `legato_showScreen` i ISR (§3.2).
- **Simple view → action:** Ved touch slukkes baglyset før skiftet (`Screen_SimpleView.c:78-86`).
- **Skærmskift og baglys:** Baglyset står, og `setDisplayIntensity()` kaldes 300 ms
  (`T_SCREENSWAP`) efter `OnShow` på action og simple view (`Display_Backlight.c:38-46`,
  `screen_Action.c:769-775`).
- **Menu ind:** Menuknappen sætter `UIREQ_GOTO_MENU` (`screen_Action.c:546-550`).
  `handleUIRequests` muter, stopper display-timerne og inputskiftets mute-timer, viser menuen og
  sætter `APP_STATE_IDLE` (`app.c:107-116`).
- **Menu ud:** Med `UIREQ_EXIT_MENU` (`Screen_Main_Menu.c:19`) vises action. Niveauet genskrives
  (AV-niveau eller `UpdateVolume`), hvis niveauet er over 0 eller AV er valgt, og der ikke er
  mutet (`app.c:117-125`).
- **I menuen:** Baglyset står på 100 %. Knapperne Digital og Pickup skjules uden modul
  (`Screen_Main_Menu.c:65-77`), mens Green bias altid er synlig.

**Legacy: display-modes (kode læst; `Screen_Display_Setup.c:14-45`, `screen_Action.c:336-369`).**

- 100/75/50/25 % giver PWM 100/60/40/15.
- Dim og off giver 100 % ved aktivitet. Når `T_DIM` (8 s) udløber, går dim til 15 % og off
  til 0. Kun off sætter `dispSleepActiveFlg` (`:345` er udkommenteret), så IR ser dim som
  dæmpet og off som slukket (§4.9).
- I begge tilfælde vises `dispOnButton` på action-skærmen.

**Legacy: omdøbning (kode læst; `Screen_Qwerty_Keypad.c`).** Navnet har 8 tegn. Tastaturet har
A–Z, ÆØÅ, cifre og symboler. Navnet gemmes ved OK.

**Legacy: fade (kode læst).** Fade ind og ud tager 40 × 50 ms og blokerer
(`Display_Backlight.c:4-24`, kaldt fra `On_Off_Control.c:919` og `:1059`).

**Krav til 2.0.** Mekanismen er [D333]'s `gui_*` og `gui_bridge` (§8).

- **FR-800 (skærmkatalog):** 2.0 får de samme skærme og betjeningsflows som 1.0 (legacy-kataloget
  ovenfor), med følgende ændringer:
  - `SN_SET` udgår.
  - `errorDisplay` bliver SYSTEM ERROR-skærmen ([D333] FR-530).
  - `autoStandby` kommer til som menuskærm og `autoStandbyWarning` som overlay ([D333] FR-815
    og FR-816).

  Forskelle fra [D333]:
  - Der er ingen monitor og ingen ventilator.
  - Green bias er altid synlig i menuen.
  - AV-valget er ingen, input 3 eller input 4.
  - Der er to AC-fejlskærme: `leftPowerMissingScreen` og `wrongAcVoltageScreen` (FR-108).
- **FR-810 (drift-skærme):** Følger [D333] FR-810.
  - Efter ON vises simple view, hvis det er slået til, og ellers action.
  - Action falder tilbage til simple view efter `T_ACTIONVIEW` (6 s, TIM-16) uden betjening.
  - Touch på simple view viser action.
  - Skærmskiftet sker fra GUI-tick, aldrig fra en timer-callback (§3.2).
- **FR-811 (display-modes):** Følger [D333] FR-811, men `T_DIM` er 8 s (TIM-17).
  - Auto-dim går til 15 %, og auto-off går til 0 %.
  - Kun auto-off tæller som slukket display over for IR (§4.9).
- **FR-812 (PWM):** Følger [D333] FR-812: 100/60/40/15.
- **FR-880 (skærmskift og baglys, Helios-specifik):** Ved skift til action eller simple view holdes
  baglyset uændret i `T_SCREENSWAP` (300 ms) efter `OnShow`. Først derefter sættes modens
  intensitet. Ved touch på simple view slukkes baglyset før skiftet.
- **FR-881 (fade, Helios-specifik):** Ved ON og OFF fades baglyset ind og ud over 40 × 50 ms.
  2.0 kører fade'en fra tick og blokerer ikke (§9.31).
- **FR-882 (menu):** Når menuen åbnes, stoppes display-timerne, og baglyset sættes til 100 %.
  Mute og genskrivning af niveauet følger FR-314. Når menuen forlades, vises action.
- **FR-815 (`autoStandby`-menuskærm):** Følger [D333] FR-815.
  - Valget er OFF eller 1–10 t i trin på 1 t. Default er OFF.
  - +/− giver tryk-hold-gentagelse som FR-304 (§9.34).
  - Værdien gemmes, når skærmen forlades. Adressen fastlægges i område 7 (§4.11).
  - Menupunktet er altid synligt. Det står nederst til venstre i `mainMenuScreen`, på samme række
    som Exit, og de 10 eksisterende knapper flytter sig ikke (beslutning 2026-11-27).
- **FR-816 (`autoStandbyWarning`-overlay):** Følger [D333] FR-816 med `T_AUTOSTBY_WARN` = 30 s
  (TIM-25). Overlayet tæller de resterende sekunder ned. Ud over [D333] gælder:
  - **Baglys:** Mens overlayet vises, er baglyset 100 %, og `T_DIM` står stille, som i menuen
    (FR-882). Når overlayet forlades, gælder FR-880 (§9.35).
  - **Annullering:** Enhver touch og enhver gyldig IR-frame annullerer slukningen og nulstiller
    nedtællingen (FR-107, FR-707). Derefter vises action. Var menuen åben, køres menu-exit
    (FR-882), så undermenuens værdi gemmes, og mute og niveau genskrives (§9.36).
- **FR-830 (SYSTEM ERROR, beslutning 2026-11-27):** Følger [D333] FR-530 med samme tekst, niveauer,
  kvittering og navigation (`app_health`, `gui_system_error`, §9.33). Kodetabellen er tilpasset
  Helios' busser. På I2C1 sidder touch. På I2C2 sidder U26, EEPROM 0x50/0x51
  (`eeProm_Functions.c:18-21`) og DAC-modulet. På I2C3 sidder U16 og U20 (`Level_Control.c:132-138`).

  | Kode | Betydning | Niveau | Forhold til [D333] |
  |---|---|---|---|
  | E11 | I2C2: SDA holdt lav | blokerende | 1:1 |
  | E12 | I2C2: SCL holdt lav | blokerende | 1:1 |
  | E13 | U26 (0x23) svarer vedvarende ikke, selvom I2C2 er fri | blokerende | U26 har U21's rolle |
  | E21 | Volumen-expander U16 (L, 0x22) død (budget brugt) | blokerende | Som E21, pr. kanal |
  | E22 | Volumen-expander U20 (R, 0x23) død (budget brugt) | blokerende | Ny |
  | E23 | I2C3: SDA holdt lav | blokerende | Ny, som E11 |
  | E24 | I2C3: SCL holdt lav | blokerende | Ny, som E12 |
  | E31 | DAC-indgangsvalg eskaleret (§9.19) | ikke-blokerende | 1:1 |
  | E41 | Reboot-loft nået (NFR-013) | ikke-blokerende | 1:1 |
  | E42 | Denne boot skyldtes en watchdog-reset | ikke-blokerende | 1:1 |

  - **E11/E12 og E23/E24:** Kriteriet er tidsbaseret som i [D333] (`T_bus` = 2 s). I2C3-driveren
    får de samme tællere som I2C2-driveren ([D333] #391).
  - **E13:** 2.0 læser U26 byte 1 som hjerteslag, og E13 latcher efter `T_E13` = 5 s uden en
    OK-læsning. Intervallet følger [D333]'s U21-hjerteslag. I 1.0 læses U26 kun ved moduldetektion
    og INT-poll (§4.6).
  - **E21/E22:** Budgettet følger [D333] #235 pr. expander. En død expander eller en låst I2C3 låser
    output-mute på U26 resten af tænd-cyklussen (§9.32).
  - **Undertrykkelse:** E13 vises ikke, når E11/E12 er sat. E21/E22 vises ikke, når E23/E24 er sat.
    Begge regler kræver, at `T_bus` er mindre end det andet kriterium (`_Static_assert`, som
    [D333]).
  - **Antal koder:** Der kan højst vises 5 koder samtidig, fx `E11 E21 E22 E31 E41`. Det er én af
    E11–E13, E21+E22 eller én af E23/E24, E31 og én af E41/E42.
  - **Ved E11–E13** kan firmwaren hverken holde eller slippe mute, fordi relæer og output-mute
    sidder på U26, som i [D333].
  - **Uden for normal drift** ejer opstart, standby og AC-fejlskærmene (FR-108) skærmen.
  - **Ingen kode** for I2C1 (touch) og EEPROM'en, som i [D333]. En låst EEPROM-slave giver E11/E12.
  - Om "switch off and on" heler U26, U16 og U20, afhænger af forsyningen i standby (§11.6).

### 4.11 Persistens

_Område 7._ EEPROM-layout fra 1.0 og ledige adresser til Auto Standby står i #1.

### 4.12 UART-testinterface

_Område 8._ Skal opfylde HIL-003 (boot-linje med reset-årsag, livsprøve, faste fejlrammer).

**Reset-årsag (WDT-005, beslutning 2026-11-27).** Legacy bruger slet ikke RCON (App og
BTL).

- **Ved opstart:** Hele RCON læses én gang og gemmes, før noget tolkes. Derefter ryddes
  alle årsagsbits, også dem over 0x3FF:
  - bit 29 (`HVDCORE`/`HVD1V8R`),
  - `VBAT` (16) og `VBPOR` (17),
  - `BCFGFAIL` (26) og `BCFGERR` (27).
- **Bit 30–31** maskeres væk, for de bærer ingen information (WDT-004 og WDT-005, målt på
  PIC32MX).
- **Boot-linjen** viser den gemte værdi.
- **Bænkbevis:** Tolkningen bevises med en baseline af den rå RCON ved en kendt POR og en
  kendt MCLR, før den bruges. Det er ikke målt på PIC32MZ DA.
- **[D333]** rydder kun WDTO og DMTO (`drv_sysio.c:149`, `:318`). De andre årsagsbits kan
  derfor slæbe med ind i senere boot-linjer (§8).

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
| TIM-24 | `T_AUTOSTBY` | OFF eller 1–10 t, i trin på 1 t (som D333) | FR-107, FR-815 (ny i 2.0) |
| TIM-25 | `T_AUTOSTBY_WARN` | 30 s (som D333) | FR-816 (ny i 2.0) |
| TIM-xx | `T_SCREENSWAP` | 300 ms | `app.h:86` |
| TIM-xx | Debounce on/off-knap og 12V-link | 20 ms | `On_Off_Control.c:277`, `:743`, `:760` |
| TIM-xx | IR-poll-vindue ved opvågning (udgår i 2.0, §9.25) | 500 ms | `IR_control.c:34` |
| TIM-xx | RC5: offset fra flanke / halvbit / ventetid på burst (D333 TIM-23: 448 / 910 µs) | 1333 / 889 µs / 40 ms | `IR_control.c:444-467` |
| TIM-xx | RC5: blokering efter Manchester-fejl | 25 ms | `IR_control.c:486` |
| TIM-xx | IR-volumen: forsinkelse før gentagelse (D333 FR-702: 200 ms) | 200 ms (legacy blokerende, 2.0 fra sidste accept, §9.25) | `IR_control.c:795` |
| TIM-xx | IR-overlay og display-view (D333 TIM-18: 3 s) | 3000 ms | `IR_control.c:309`, `:361` |
| TIM-xx | Noise-guard ved opvågning | 500 ms | `On_Off_Control.c:16` |
| TIM-xx | Poll af venstre forsyning | 10 ms × 5 samples | `On_Off_Control.c:1255-1256` |
| TIM-xx | Debounce af 12V-link (faldende flanke) | 30 ms | `On_Off_Control.c:116` |
| TIM-xx | ON-trin 1 / 2 / 3 / 4 | 500 / 500 / 1500 / 3000 ms | `On_Off_Control.c:900`, `:910`, `:921`, `:964` |
| TIM-xx | ON-trin 5, stabilisering (D333 `T_STAB`: 21/31 s) | 18 000 ms, phono 23 000 ms | `On_Off_Control.c:1028-1029` |
| TIM-xx | ON-trin 6 / 7 | 1000 / 500 ms | `On_Off_Control.c:1062`, `:1092` |
| TIM-xx | Logo-blink under opstart | 250 ms | `On_Off_Control.c:898` |
| TIM-xx | Baglys-fade ind/ud (legacy blokerende, 2.0 fra tick, §9.31) | 40 × 50 ms | `Display_Backlight.c:4-24` |
| TIM-xx | OFF: mute → forsyninger af / → `#0:00;` / → sleep | 5 / 700 / 50 + 50 ms | `On_Off_Control.c:1112`, `:1121`, `:1137`, `:1168`, `:1179` |
| TIM-xx | AC-mismatch: LED skifter / gentjek | 1000 / 200 ms | `ac_check.c:120-121` |
| TIM-xx | Inputskift: mute-hold kort / langt (D333 TIM-08: 200 / 2000 ms) | 200 / 2000 ms | `MB_IOexp_U26_Control.c:479` |
| TIM-xx | Inputskift: venten efter analog mute | 20 ms (blokerende) | `MB_IOexp_U26_Control.c:464` |
| TIM-xx | Make-before-break: venten pr. skrivning (D333 TIM-09: 1 ms pr. fase) | 2 ms × 6 skrivninger | `Level_Control.c:133-164` |
| TIM-xx | Volumen-repeat: første / gentagelse (D333 TIM-15: 400 / 120 ms) | 400 / 120 ms | `screen_Action.c:32-33` |
| TIM-xx | Volumen-repeat: stop uden touch-opdatering / maks. antal gentagelser | 250 ms / 84 | `screen_Action.c:34-35` |
| TIM-xx | DAC-init: settling før `dacSetup` (D333 TIM-20: 500 ms) / efter volume-rate | 500 ms / 2 × 150 ms (blokerende, FR-400) | `MB_IOexp_U26_Control.c:509-524`, `Dac_Control.c:898`, `:907` |
| TIM-xx | Digitalt skift: efter kanal-mute / BCK-toggle / før unmute | 75 + 100 ms / 2 × 5 ms / 30 ms | `Dac_Control.c:926-962` |
| TIM-xx | Digitalt skift: retry-interval / maks. antal (D333 §9.28) | 500 ms / 10 | §9.19 |
| TIM-xx | Fs-visning: hold efter ændring | 350 ms | `screen_Action.c:1023-1056` |
| TIM-xx | S/PDIF-Fs: første læsning / retry / maks. retries | 30 ms / 20 ms / 10 | `screen_Action.c:1142-1301` |
| TIM-xx | S/PDIF-Fs: DIR re-init maks. pr. lock / afstand / overvågning under lock | 3 / 600 ms / 200 ms | `screen_Action.c:1142-1301` |

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
| Eksekveringsmodel, superloop med flag-ISR'er | [D333] NFR-010/011, `SW_U3_REBUILD` | Mekanisme 1:1 | Intet eget bænkissue. Bærer alle paritetstest på bænken (D333 #52–#56) |
| DMT-watchdog og reboot-loft | [D333] NFR-013 | 1:1, undtagen RCON-rydningen, som følger §4.12 (WDT-005) | Bænkbevist 2026-10-21 ([D333] NFR-013) |
| Auto Standby | [D333] FR-107, FR-815, FR-816 (`app_standby.c`) | 1:1 (#1) | Bænkbevist 2026-06-30 med midlertidig tidsskala (D333 #115) |
| Power-sekvenser som tick-baseret state machine | [D333] `svc_power.c` | Mekanisme; trin og tider fra Helios (§4.1) | Bænkbevist 2026-06-25, fuld on/off-paritet (D333 #52) |
| Standby i deep sleep/IDLE med opvågning via INT0/CN | Ingen i [D333] | Helios-specifik, bygges ud fra [LEGACY] | — |
| Volumen-attenuator med make-before-break | [D333] FR-300–306, `drv_volctl`, `svc_volume` | Mekanisme. Helios har to expandere (L/R), indeks 0–84, tre MBB-faser og balance (§4.3) | Bænkbevist (D333 #54, M9-paritet med Audio Precision) |
| Ikke-blokerende mute og inputskift med hold på 200/2000 ms | [D333] FR-202, FR-310–316, `svc_mute`, `svc_input`, `app_audio_ctrl` | Mekanisme. Helios' inputs, relæbits og −6 dB-inputs (§4.2) | Bænkbevist (D333 #54, #170, #174, #175) |
| AV-bypass og level match i volumenkonteksten | [D333] FR-302, FR-355, `SvcVolume_SetContext` | Mekanisme. Helios' AV-inputs 3/4 og indeks 66 | Bænkbevist (D333 #169) |
| DAC-modul: init, digitalt skift, lock-gate, filtre og status | [D333] FR-203, FR-400–406, `drv_es9039`, `drv_ak4118`, `drv_u26`, `svc_dac` | Mekanisme og registersekvenser 1:1. Helios' input-numre 7–11 og S/PDIF-Fs fra Helios' tilstandsmaskine (§9.15) | Bænkbevist (D333 #53, Audio Precision, lukket 2026-07-09) |
| Retry af fejlet digitalt skift | [D333] §9.28, `svc_dac` | 1:1 (§9.19) | Host-verificeret (D333 #234, #245, #408) |
| Green bias | Ingen i [D333] | Helios-specifik, bygges ud fra [LEGACY] (FR-410) | — |
| IR: RC5-dekoder, toggle, hold og overlays | [D333] FR-700–704, `drv_ir_rc5`, `app_ir`, `gui_remote_view` | Mekanismen 1:1 med RC5X og Helios' tider (§9.20–9.25). Power-koderne og opvågning fra standby er Helios-specifikke (FR-706) | Bænkbevist (D333 #56, #162, #280 del B) |
| IR-kilde | [D333] FR-705, `app_settings`, `gui_ir_source` | 1:1, gemmes straks (§9.27) | Bænkbevist 2026-06-30, front/bag (D333 #56) |
| SYSTEM ERROR med fejlkoder | [D333] FR-530, §9.41, `app_health`, `gui_system_error` | Mekanismen 1:1. Kodetabellen er Helios' (FR-830), med E22–E24 og hjerteslag på U26 | Host-testet (`test_app_health.c`). Skærmen er bænkbevist for E21, E11 og E42 (D333 #392) |
| Mute-lås ved død volumen-expander | [D333] §9.40, `SvcMute_LockMuted` | 1:1, men udløst af U16/U20 og I2C3 (§9.32) | Bænkbevist 2026-10-27 (D333 #366) |

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
    - **2.0:** Volumensekvensen slår ikke IR fra. Beskyttelsen går den anden vej: IR-ISR'en
      sampler i ca. 24 ms (§9.20), og en bus-guard udsætter dekodningen, mens en
      I²C-transaktion kører, som [D333] §9.19 (`DrvIrRc5_SuspendDecode`). En IR-frame, der
      tabes under et volumenskift, accepteres.
    - **Evidens:** [D333] #173 er verificeret på bænken: 18 s med tung IR-spam gav 111 rene
      MBB-par og ingen korruption.
    - **Bænktest på Helios:** Testen gentages med IR-spam under volumenskift. Den kan
      automatiseres med en Arduino som IR-kilde og UART som orakel.
13. **(adfærd) User-mute holder på tværs af digitale inputskift** (beslutning 2026-11-27).
    - **Legacy:** `setDigitalInput()` unmuter DAC-kanalen på S/PDIF-grenen uden at se på
      `muteFlg` (`Dac_Control.c:957`). Ved user-mute på et digitalt input er relæerne
      lukkede, og ved digital → digital springes det analoge mute over (§4.6). Der spiller
      derfor lyd, mens mute vises (kode læst, ikke set på bænken).
    - **Legacy, samme årsag:** `setInputRelay()` muter og unmuter DAC-kanalen på et digitalt
      input, hver gang holdet udløber, og når niveauet forlader 0
      (`MB_IOexp_U26_Control.c:424-429`, `Level_Control.c:102`). Det giver et mute-blip og
      150 ms blokering. USB unmutes her med kabel tilsluttet, men uden at se på lock.
    - **2.0:** DAC-kanalen unmutes kun ét sted, i `svc_mute` (§9.11). Det sker, når holdet er
      udløbet, der ikke er user-mute, og der er lock, hvis inputtet er USB (FR-404 i [D333]).
      Der er intet ekstra mute-blip, og USB unmutes aldrig uden lock.
      `svc_dac`'s valg af input efterlader kanalen mutet. [D333's `SvcDac_SelectInput`
      unmuter selv efter S/PDIF-sekvensen (`svc_dac.c:198-241`). Det ændres, medmindre det
      viser sig, at D333's `svc_mute` allerede muter igen bagefter.]
    - **Bænktest:** mute, skift til et S/PDIF-input og mål, at der er stille. Den kan
      automatiseres med en Arduino som IR-kilde og UART som orakel.
14. **(adfærd) Phono-inputtet gendannes også uden DAC-modul** (beslutning 2026-11-27).
    - **Legacy:** `handlePhonoConfiguration()` kaldes ikke (`On_Off_Control.c:1045`), så
      `maxInp` er 5, når ON5 validerer inputtet (`:978`, `:1020`). Med phono-modul og uden
      DAC-modul bliver et gemt input 6 derfor til input 1, og phono-tiden på 23 s
      (`:1031`) bruges aldrig (kode læst, ikke set på bænken).
    - **2.0:** `maxInp` afledes af begge moduler, før inputtet valideres, som [D333] FR-110.
      Phono gendannes og får phono-tiden i ON5 (FR-200).
    - **Bænktest:** Helios med kun phono-modul, input 6 valgt, sluk og tænd.
15. **S/PDIF-Fs opsamles uafhængigt af skærmen** (beslutning 2026-11-27).
    - **Legacy:** `DIR_FS_AcqTask` kaldes kun fra `updateActionScreen()`
      (`screen_Action.c:1363-1367`). Kommer lock, mens en anden skærm vises, sker der ingen
      re-init af DIR'en ved lock-flanken, og Fs læses ikke.
    - **2.0:** Helios' tilstandsmaskine kører i `svc_dac` i hvert tick, uanset skærm
      (NFR-010, NFR-015). Tiderne er som i legacy (§4.6). GUI'en læser kun resultatet.
      [D333 har sin egen Fs-læsning, `SvcDac_GetSpdifFsHz`. Michael har valgt at
      bevare Helios' tilstandsmaskine.]
    - **Synlig adfærd:** uændret på action-skærmen. Fs er korrekt fra første visning efter
      et skærmskift.
    - **Bemærk:** Lyden går gennem DAC'ens S/PDIF-dekoder, og DIR'en bruges kun til Fs
      ([D333]'s handoff). Det er ikke bekræftet på Helios.
16. **Fs-opslag tjekkes mod tabellens længde** (beslutning 2026-11-27).
    - **Legacy:** DIR'ens Fs-felt er 0–15, men `dacFsTabel` har kun 15 indgange
      (`ui_globals.c:61-76`). Værdien 15 læser ud over tabellen, sandsynligvis ind i
      `usbFsTabel`. USB-tabellen er erklæret med 16 indgange, men kun 15 er udfyldt
      (`:78-93`), så USB-Fs 15 viser en tom streng.
    - **2.0:** Værdier uden en indgang vises som "NA", som `dacFsTabel` indgang 13.
17. **Død DAC- og statuskode videreføres ikke** (beslutning 2026-11-27), som §9.9. Følgende
    kan ikke nås eller har ingen virkning, og det overføres ikke:
    - `lockedButNoFs_Callback` (`screen_Action.c:320-324`), som registreres ingen steder,
      og grenen i `updateActionScreen` (`:1415-1423`).
    - `dsdFilter`: `dacSetDSDFilter()` og begge knapper er tomme (`Dac_Control.c:686-689`,
      `Screen_Digital_Setup.c:63-64`). EEPROM-byte 0x08 bliver **reserveret**. 2.0 læser og
      skriver den ikke, og layoutet fra 1.0 bevares (område 7).
    - Fejlstatus-skelettet: `errorCheckFlg` (`On_Off_Control.c:974`, `:1110`),
      `saveErrorStatus` og `getErrorStatus` (`eeProm_Functions.c:371-386`) og de
      udkommenterede fejlbits (`MB_IOexp_U26_Control.c:678-679`).
    - `handlePhonoConfiguration()` (`MB_IOexp_U26_Control.c:486-507`), som erstattes af
      §9.14.

    Ingen adfærd ændres.
18. **(adfærd) Green bias på AV følger det faste indeks 66** (beslutning 2026-11-27).
    - **Legacy:** Bias vælges ud fra `curLvl` (`MB_IOexp_U26_Control.c:365-389`). På AV står
      relæerne fast på 66 (§4.2), men bias følger det skjulte `curLvl`. Det kan give LOW,
      mens udgangen står højt.
    - **2.0:** På et AV-input vælges bias ud fra 66. På alle andre inputs bruges `curLvl`
      som i legacy (§10.3).
19. **(adfærd) Et fejlet digitalt skift prøves igen** (beslutning 2026-11-27), som [D333]
    §9.28.
    - **Legacy:** `setDigitalInput()` skriver DAC-registrene uden at tjekke resultatet
      (`Dac_Control.c:926-962`). Fejler en skrivning midtvejs, kan DAC'en blive mutet på det
      gamle input, mens det nye vises.
    - **2.0:** Fejler FR-203 eller lock-gaten (FR-404), husker `svc_dac` det ønskede input og
      prøver hele DAC-delen igen hver 500 ms, højst 10 gange. Budgettet gælder både transiente
      fejl og NACK, for én NACK kan være et glitch på I²C2 ([D333] #408). Kun en
      programmeringsfejl (`ERR_PARAM`) eskalerer straks. Tjekket for, om DAC'en svarer, lukker
      stadig på én NACK, men det er selvhelende og bruger ikke budgettet ([D333] #312). Et nyt
      skift starter med fuldt budget, og et skift til et analogt input annullerer ønsket.
    - **Synlig adfærd:** Mens skiftet venter eller er eskaleret, vises "NO SIGNAL" (FR-406).
      En eskalering vises som E31 på SYSTEM ERROR-skærmen (FR-830, beslutning 2026-11-27), som
      [D333] FR-530. [D333] dæmper desuden hængelås-ikonet. Det er ikke afgjort for Helios.
    - **Evidens:** host-verificeret i [D333] (`test_svc_dac.c`, #234, #245, #408).
20. **IR samples i CN-ISR'en som [D333]** (beslutning 2026-11-27).
    - **Legacy:** ISR'en sætter kun et flag, og main-loopet dekoder senere ud fra antagelsen
      om, at det står på den første faldende flanke (§4.9). Kører main-loopet længe, rammer
      samplingen forkert (udledt, ikke målt). Dekodningen blokerer main-loopet i 24–90 ms
      pr. frame.
    - **2.0:** [D333]'s mekanisme 1:1 (`drv_ir_rc5`): sampling i CN-ISR'en på faldende flanke
      med interrupts slået fra og en `CONVENTION-EXCEPTION` (NFR-010, NFR-011). Synkroniseringen
      er bundet af CORETIMER, interrupt-tilstanden gendannes ved hver udgang, og der er en
      bus-guard mod I²C (§9.12). Den rene `DecodeHalfBits` er host-testet.
    - **Helios-tilpasning:** RC5X (kommando 64–127) sendes videre, så 123 og 124 virker.
      [D333 kasserer kommandoer over 63.]
    - **Tider:** [D333]'s 448 / 910 µs er afstemt efter D333's modtager. Helios' tider
      bevises på Helios' egen modtager. Helios 1.0's 1333 / 889 µs (§5) er udgangspunktet.
    - **Bænktest (kan automatiseres, HIL-001/003):** En Arduino med IR-LED sender alle
      kommandoer som RC5 og RC5X med hold og toggle, også under volumenskift. Firmwarens
      UART-hændelseslinje er oraklet, og ingen frame må tolkes forkert.
21. **(adfærd) I standby tæller kun 12 og 123** (beslutning 2026-11-27).
    - **Legacy:** `PollIrForOn` sender hver frame gennem hele `handleIrCommand`
      (`IR_control.c:42-64`, `:709-847`). Volumen og direkte inputvalg ændrer derfor
      `curLvl` og `curInp` i standby, og display-logikken kan køre (udledt, ikke set på
      bænken).
    - **2.0:** I standby er 12 (`com_on_off`) og 123 (`com_power_on`) de eneste gyldige
      tænd-årsager fra IR. Alle andre frames kasseres uden sideeffekter.
    - **Test:** på host. Alle andre kommandoer sendes i standby, og tilstanden skal være
      uændret.
22. **(adfærd) Under opstart virker kun IR-sluk** (beslutning 2026-11-27).
    - **Legacy:** `wakeUpFlg` ryddes i ON4 (`On_Off_Control.c:946`), og derefter blokerer
      `handleIrCommand` kun i menuen (`IR_control.c:716-730`). Volumen, input, mute og
      overlays virker derfor i ON5–ON7, mens enheden er mutet (udledt).
    - **2.0:** Fra ON1 til ON7 ignoreres al IR undtagen 12 og 124. De slukker fra ON4, som
      on/off-knappen (FR-106). Gatingen er [D333]'s (D333 FR-102, FR-703, bænkbevist i
      D333 #280 del B), og sluk-muligheden er Helios'.
    - **Test:** på host. Volumen sendes i ON5, og `curLvl` skal være uændret. 124 i ON5 skal
      starte OFF-sekvensen.
23. **(adfærd) Et IR-inputvalg, der intet ændrer, gør intet** (beslutning 2026-11-27).
    - **Legacy:** Direkte valg sætter `irInputChangeFlg`, også når `curInp` ikke ændres. Det
      gælder kode 6 uden phono-modul og valg af det aktuelle input (`IR_control.c:146-150`).
      Flaget kører `setInput()` igen (`screen_Action.c:1335-1359`,
      `Screen_SimpleView.c:47-56`). Det giver et mute-hold (200 eller 2000 ms) og et kort
      lydudfald.
    - **2.0:** Et input, der ikke findes, afvises, før der sker noget, som [D333] #91
      (`AppCommands_IsDirectInputAllowed`). Er inputtet allerede valgt, sker der intet. Det
      tjekkes ved implementeringen, om [D333]'s `AppAudioCtrl_SetInput` allerede ignorerer
      et genvalg.
    - **Touch og UART:** Om det samme gælder genvalg fra dem, afgøres i område 6 og 8.
    - **Test:** på host.
24. **(adfærd) Et tryk på et IR-overlay genstarter 3 s-timeren** (beslutning 2026-11-27).
    - **Legacy:** På Filter-, DSD-LP- og Gain-overlayet ændrer et tryk værdien, men timeren
      genstartes ikke (`IR_control.c:356-426`). Overlayet lukker 3 s efter første tryk. På
      Display-overlayet genstartes timeren (`:335-341`).
    - **2.0:** [D333]'s `gui_remote_view` 1:1. Et tryk på overlayet udfører handlingen,
      viser overlayet igen med den nye værdi og genstarter timeren. Det gælder for alle
      fire overlays. Bænkbevist i [D333] #56.
25. **IR blokerer ikke main-loopet** (beslutning 2026-11-27).
    - **Legacy:**
      - Ved hold blokeres i 200 ms (`IR_control.c:795`), og frames tabes imens.
      - En Manchester-fejl giver 25 ms ekstra (`:486`).
      - `PollIrForOn` blokerer i op til 500 ms ved opvågning, også fra INT0-ISR'en (§3.2).
    - **2.0:**
      - **Hold** som [D333] FR-702: Første gentagelse kommer tidligst 200 ms efter sidste
        accept, og derefter giver hver frame ét trin, indtil togglebitten skifter. De 200 ms
        er Helios'.
      - **Fejlframe:** En ugyldig frame kasseres uden ventetid.
      - **Opvågning:** Der er intet separat IR-vindue. Tænd-koden søges inden for
        noise-guarden på 500 ms (FR-120, §9.6). TIM-rækken for IR-poll-vinduet udgår.
    - **Synlig adfærd:** stort set uændret.
26. **Død IR-kode videreføres ikke** (beslutning 2026-11-27), som §9.17. Følgende har ingen
    virkning og overføres ikke:
    - `ignoreToggleFlg` og `ignoreToggleCnt` (`IR_control.c:21-23`, `:685`, `:700`).
    - `irOneStepVol` (`:24`).
    - `isImmediateWhenDisplayOff`, `isDeferredUiWakeCommand` og `isVolumeCommand`
      (`:574-592`).
    - `irActionScreenDisplayTiming` og `irSimpleViewScreenDisplayTiming` (`:606-632`).
    - Kode 21 (`com_monitor`, `KeyMonitor`, `app.h:97`, `:107`). Helios har ingen
      monitor-funktion, så 2.0 ignorerer kode 21. [D333 bruger kode 21 til monitor.]

    Ingen adfærd ændres.
27. **(adfærd) IR-kilden gemmes straks som [D333]** (beslutning 2026-11-27).
    - **Legacy:** Valget lægges straks ud på `IR_SOURCE`, men gemmes først i EEPROM 0x05, når
      der trykkes "tilbage til menu" (`Screen_IR_Source_Setup.c:13-33`). Slukkes enheden på
      skærmen, bruges den gamle modtager efter næste tænd. EEPROM-værdien valideres ikke, så
      enhver værdi ≠ 0 giver front (`On_Off_Control.c:625-628`).
    - **2.0:** [D333] FR-705 1:1 (`app_settings`, `gui_ir_source`). Valget lægges ud på
      pinden og gemmes straks. Kodningen er 1 = front og 0 = bag, og standardværdien er front.
      Begge dele er ens i Helios og [D333].
    - **Ugyldig EEPROM-værdi:** Hvordan den tolkes, afgøres i område 7. [D333] tolker kun 1
      som front. Om den validerer ved indlæsning, er ikke tjekket.
28. **Inputnavne er data, aldrig format** (beslutning 2026-11-27).
    - **Legacy:** Tastaturet tillader `%` i et inputnavn (`Screen_Qwerty_Keypad.c:36`). Navnet
      bruges som format i `sprintf(cCharBuffer2, inpNames[...])` (`Screen_SimpleView.c:51`,
      `:92`, `uart_control.c:308`). Et navn som `CD%s` giver udefineret adfærd og kan skrive ud
      over `cCharBuffer2[16]` (kode læst).
    - **2.0:** Navnet kopieres som data med en funktion, der har længdegrænse, fx
      `snprintf(buf, sizeof buf, "%s", name)`. `%` er et almindeligt tegn i navnet, og
      tastaturet er uændret. Det dækkes af en host-test med `%` i navnet.

    Den synlige adfærd er den samme for alle navne uden `%`.
29. **Touch uden håndrettelser i genereret kode, med én undtagelse** (beslutning 2026-11-27),
    som [D333] rebuild (NFR-015).
    - **Legacy:** `le_gen_harmony.c:114-130` er rettet i hånden med `ActionTouch_On*`-kald til
      volumen-repeat. `drv_touch_controller.c:403-415` genstarter I2C1 og kalder
      `ActionTouch_OnError` ved touch-fejl. Begge rettelser fjernes ved en regenerering
      (kode læst).
    - **2.0:** Touch-hooks går via [D333] `touch_bridge.c`, som har sin egen `SYS_INP`-lytter.
      Touch-genopretningen er [D333]'s sanktionerede blok i `DRV_TOUCH_STATE_ERROR`
      (#60), der genindsættes efter en fast procedure. Blokken rydder en hængende tryk-tilstand
      før I²C-genstarten (#103).
    - **Synlig adfærd:** Den er uændret, bortset fra at et tryk, der hænger ved en I²C-fejl, nu
      slippes.
30. **Død GUI-kode videreføres ikke** (beslutning 2026-11-27), som §9.9, §9.17 og §9.26.
    Følgende har ingen synlig effekt i legacy (kode læst):
    - `prevStateForOverlay` tildeles aldrig, så overlayenes `OnHide` sætter tilstanden til
      `INIT` (`Screen_SimpleView.c:256-272`, `app.c:84`). Den nye skærms `OnShow` overskriver
      den straks.
    - `uiOverlayActive` sættes aldrig til 1.
    - Kun `filterSimpleView_OnShow` sætter `APP_STATE_IDLE` (`:179`), så UART behandles på det
      ene overlay og ikke på de to andre. Forskellen forsvinder med §9.3.

    I 2.0 modelleres overlays efter NFR-016, hvor tilstand og skærm er adskilt. Ingen adfærd
    ændres.
31. **Baglys-fade blokerer ikke** (beslutning 2026-11-27, FR-881).
    - **Legacy:** Fade ind og ud tager 40 × 50 ms i ét blokerende kald (`Display_Backlight.c:4-24`,
      kaldt fra `On_Off_Control.c:919` og `:1059`). Main-loopet står stille i 2 s (kode læst).
    - **2.0:** Det samme antal trin og den samme varighed, men hvert trin tages fra tick (§3.2).
    - **Synlig adfærd:** Den er uændret.
32. **(adfærd) En død volumen-expander låser mute** (beslutning 2026-11-27), som [D333] §9.40.
    - **Legacy:** Skrivningerne til U16 og U20 tjekkes ikke (`Level_Control.c:132-138`). Hvad
      udgangen gør, når en expander står i høj-Z, er ikke målt på Helios (§11.6). I [D333] gav det
      næsten fuld volumen uden volumenstyring.
    - **2.0:** Er en expanders budget brugt (E21/E22), eller er I2C3 låst (E23/E24), låser
      `svc_mute` output-mute på U26 resten af tænd-cyklussen (`SvcMute_LockMuted`). Ingen unmute
      slipper låsen, og kun næste boot rydder den. Resten af tænd-sekvensen fuldføres uændret.
    - **Forskel fra [D333]:** Mute sidder på I2C2 og volumen på I2C3, så låsen virker også ved en
      låst I2C3.
    - **Synlig adfærd:** Forstærkeren er tavs, og SYSTEM ERROR viser koden (FR-830).
33. **(adfærd) Eskalerede fejl vises på SYSTEM ERROR-skærmen** (beslutning 2026-11-27), som
    [D333] §9.41.
    - **Legacy:** `errorDisplay` vises ingen steder (§4.10). I²C-fejl ses højst i UART-loggen.
    - **2.0:** Koderne og reglerne står i FR-830.
34. **(adfærd) Tryk-hold gentager på volSettings og autoStandby** (beslutning 2026-11-27), som
    [D333] §9.10.
    - **Legacy:** Start- og maxniveau ændres ét trin pr. tryk, og `OnReleased` er tom
      (`Screen_Volume_Settings.c:63-107`, kode læst).
    - **2.0:** +/− genbruger [D333]'s `gui_vol_repeat` med samme timing og stopregler som FR-304
      (FR-303, FR-815). Der gemmes stadig først ved exit, så hold slider ikke på EEPROM'en.
    - **Synlig adfærd:** Holdes +/− nede, gentages trinnet. Et kort tryk giver ét trin som før.
35. **(adfærd) Auto Standby-advarslen vises med fuldt baglys** (beslutning 2026-11-27, FR-816).
    - **Legacy:** Funktionen findes ikke.
    - **Forskel fra [D333]:** `gui_auto_timeout_overlay.c` sætter ikke baglyset, så advarslen
      vises på 0 % ved auto-off og på 15 % ved auto-dim (kode læst på `origin/main`).
    - **2.0:** Baglyset er 100 %, og `T_DIM` står stille, mens overlayet vises.
    - **Synlig adfærd:** Advarslen kan altid ses. Bør foreslås tilbage til [D333].
36. **(adfærd) Annulleret Auto Standby i menuen går ud via menu-exit** (beslutning 2026-11-27,
    FR-816).
    - **Legacy:** Funktionen findes ikke.
    - **Forskel fra [D333]:** Annullering viser altid `actionScreen` direkte. På Helios muter
      menuen (FR-882, FR-314), så en åben menu ville efterlade lyden mutet.
    - **2.0:** Annullering viser stadig action. Var menuen åben, køres den normale menu-exit først:
      undermenuens `OnHide` gemmer, niveauet genskrives, og mute hæves efter FR-314.
    - **Synlig adfærd:** Brugeren lander på action med lyd, som efter Exit i menuen.

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
2. **PCM-filtret går rundt på IR, men ikke på touch** (beslutning 2026-11-27).
   - IR har én tast, og den går fra 7 til 1 (`IR_control.c:366-369`).
   - Touch har op og ned og stopper ved 1 og 7 (`Screen_Digital_Setup.c:66-75`).
   - Forskellen er en parameter, som brugeren kan mærke, og den følger 1.0 (§1).
3. **Green bias følger `curLvl`, ikke det effektive relæ-indeks** (beslutning 2026-11-27).
   - Digital gain, level match og balance flytter ikke bias-trinnet
     (`MB_IOexp_U26_Control.c:365-389`).
   - Tærsklerne er de samme som i 1.0 (§4.6). Undtagelsen er AV (§9.18).

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
   - _Område 6 (FR-830, §9.32):_ Hvilket niveau giver udgangen, når U16 eller U20 står i høj-Z?
     Det kan måles på bænken ved at holde SDA3 til GND, som [D333] gjorde.
   - _Område 6 (FR-830):_ Mister U26, U16 og U20 forsyningen i standby, så en tænding er en POR?
     Sidder EEPROM'en på standby-rail'en? Det afgør, om "switch off and on" heler E1x og E2x.

---

*Dokumentet vedligeholdes efter samme meta-regel som [D333]: huller opdaget under
implementeringen rettes her, før koden skrives.*
