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

1. **PRD for 2.0 (#1), branch `docs/prd-2.0`:** Område 1–5 er gennemgået. I område 6 (GUI) er
   de 8 fund placeret, legacy-afsnittet i §4.10 er skrevet, og kravene til skærmkatalog og skift
   (FR-800–812, FR-880–882) er skrevet, og det samme er SYSTEM ERROR (FR-830) og Auto Standby
   (FR-815, FR-816), Pickup og AV (FR-850, FR-855, FR-861) og GUI-001 (§3.3, §9.39)
   (2026-11-27, se log). **Område 6 er gennemgået.** **Område 7 er gennemgået**
   (§4.11, §9.40–9.43, se log "område 7, læst"). **Område 8 er gennemgået**
   (§4.12, §9.44–9.51, §10.5, se log "område 8, læst"). **Område 9 (USB-servicestick, §4.14) er
   læst**, og fund 1–5 er placeret i §9.52–9.56. Fund 6–10 mangler (se log "område 9, læst"), og så §4.14.
   - D333-referencerne i område 1–5 er tjekket mod `origin/main` (2026-11-27, se log). Det
     lokale D333-checkout er stadig bagud. Rør det ikke, men læs med
     `git -C D:/MPLAB/d333 show origin/main:<fil>`.
   - **Nyt i D333 siden 2026-10-28, som Helios skal tage stilling til:** §9.38 gammel ACK
     fjernes før kommandofilen (#417, §4.14). FR-861/§9.42 og FR-850/§9.43 er afgjort
     (Helios §9.37, §9.38), og §9.40 og E31 er afgjort med FR-830.
   - Foreslå §9.35 (baglys på overlayet) og §9.36 (menu-exit ved annullering) tilbage til D333.
   - Afgør, om genvalg af det aktuelle input fra touch heller ikke gør noget (§9.23).
   - **Åbent fra område 5:** IR-tiderne skal bevises på Helios' modtager (§9.20).
     UART-hændelseslinjen for IR fastlægges i område 8.
   - **Åbent fra område 4, 6 og 7:** §11.6 har seks hardwarespørgsmål til Michael (U26 bit 1.2,
     autoincrement på DAC-modulets expander, polariteten på green bias, udgangsniveauet ved
     høj-Z på U16/U20, om standby er en POR af expanderne, og om EEPROM'en er en 24LC04B). FR-403 og FR-406
     afhænger af autoincrement. Poll-intervallet for DAC-status i FR-403 er ikke fastlagt.

   Arbejdsgang:
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

### 2026-11-27 (område 9, læst)

Servicesticken er læst i `app_usb_cmd.c` (uændret siden `v1.0`), `tasks.c:93-104`,
`On_Off_Control.c` og `ac_check.c`. [D333] PRD §4.14 (FR-1300–1303) og §9.38 er læst på `origin/main`
(`fe1787d`), og SVC-001–009 er læst.

- **Filerne:** `/mnt/myDrive1/584_CMD.TXT` læses, og `584_ACK.RTF` skrives (`app_usb_cmd.c:40-41`).
- **Kommandoer:** `VOLTAGE` eller `VOLT` med `HIGH`, `LOW`, `1` eller `0` (værdien er
  case-insensitiv), `FW` (no-op) og `BOOT` (16-bit tæller fra 0x84). `SN:` er udkommenteret, selv om
  headeren nævner den.
- **Fund til placering:**
  1. **Vinduet:** USB kører kun ved `!powerOnFlg`, men i standby sover CPU'en. Reelt er det boot-stien
     (højst ca. 0,5 s), AC-check til ON4 (ca. 2,5 s) og mismatch-skærmen. **Placeret: §9.52** (som
     [D333]: RUNNING og AC-fault, et mount under opstart venter). VBUS i ON står i §11.6.
  2. `APP_SystemReset()` efter et VOLTAGE-skift (`:425`) kan ramme ON1–ON3 uden ordnet OFF. [D333]
     resetter ikke (`ACTION: Power-cycle required`). **Placeret: §9.53** (som [D333], intet reset,
     heller ikke på mismatch-skærmen).
  3. Der gemmes før kvitteringen, og kvitteringen viser den parsede værdi, også når gemningen
     fejler (`:348-350`). En skrivefejl annullerer kun resettet (SVC-002, SVC-004). **Placeret:
     §9.54** (som [D333]. Volantes "bevis først" er fravalgt).
  4. **Parseren:** Nøglerne skelner mellem store og små bogstaver, ukendte linjer ignoreres tavst, den
     sidste VOLTAGE vinder, og der læses højst 9 linjer og 511 B. Desuden findes aliaset `VOLT` og
     `1`/`0` (SVC-008). [D333] FR-1301. **Placeret: §9.55** (ren [D333], `VOLT` og `1`/`0`
     udgår).
  5. **Kvitteringen** har titlen `THE GRYPHON HELIOS`, `FIRMWARE VERSION:`, `VOLTAGE SETTING:` og
     `BOOT COUNTER:`, men ingen STATUS, ERROR, ACTION eller BOOTLOADER (SVC-007). **Placeret:
     §9.56** ([D333]'s ramme, 1.0's titel og etiketter, ingen BOOTLOADER-linje).
  6. **Den gamle kvittering** truncates og slettes ikke, før kommandofilen læses. [D333] #417.
  7. **Læsefejl:** `(size_t)-1` i en `uint32_t` tolkes som data, så den gamle buffer parses
     (`:295-296`). En tom fil giver ingen kvittering, og ACK-handlet tjekkes ikke (`:396`).
  8. **SN** er udkommenteret, og kvitteringen har intet SN.
  9. [D333]'s `ERROR` og `ERROR=CLEAR`: Helios har ingen gemt fejlstatus (§9.17).
  10. **Ingen synlig respons** ved fejl eller succes. [D333] har kun loggen (#253) (SVC-005).
- **Rettet:** §9.2 sagde "USB kun i standby". Den henviser nu til §9.52.
- **Fælles erfaring:** Tilføjelsen "Efterprøvet i Helios" i SVC-009 er forkert, for CPU'en sover i
  standby. Rettelsen er foreslået og venter på Michael.
- **Bemærket fra område 8:** §9.3 ("altid aktiv", fejlramme) modsiger §9.51 (bytes uden for
  vinduet kasseres).

### 2026-11-27 (område 8, læst)

UART-testinterfacet er læst i `uart_control.c` (uændret siden `v1.0`), `app.c` og
`On_Off_Control.c`, og [D333] PRD §4.12, §9.9, §9.29, §9.35 og §9.45 er læst på `origin/main`
(`fe1787d`):

- **Linjen:** UART1 kører 115200 8N1 (BRG 162 med BRGH og PBCLK2 75 MHz,
  `plib_uart1.c:94-100`, `plib_uart1.h:64`). RX polles uden ringbuffer, og stdio går til UART1.
  TX venter på UTXBF uden timeout (`plib_uart1.c:225`).
- **Hvor kommandoer læses:** På actionScreen og simpleView efter opstart (`app.c:192`, `:214`) og
  i `APP_STATE_IDLE` uden opstartstjek (`app.c:280`). `APP_STATE_IDLE` er hovedmenuen og
  init-tilstanden. Om den også gælder i standby, er ikke afklaret. RX tømmes i ON5
  (`On_Off_Control.c:975`).
- **Rammen `$c:vv;`** (`uart_control.c:313`): Der ventes 10 ms blokerende, og så læses alt i
  FIFO'en. Kun position 0, 2 og 5 tjekkes. Værdien læses med `sscanf("%2hhu")`, så `$1:0X;` giver
  værdien 0 og udføres. Står der flere rammer i FIFO'en, udføres kun den første.
  Kvitteringen er `#c:vv;\r\n`.
- **Kommandoer:**
  - `1` volumen: over maxLvl ignoreres, og kvitteringen viser curLvl.
  - `2` input: `≤ maxInp` accepteres, også 0. Mute og relæ skiftes med 50 ms blokerende ventetid,
    og der gemmes ikke.
  - `3` mute: alt andet end 1 er unmute.
  - `5` IR-kilde: pinden sættes direkte, uden appData og uden EEPROM. Kvitteringen gentager alle
    værdier, også ugyldige.
  - `6` fabriksreset (§9.42).
  - `8:00` FW og spændingssetting.
  - `9:00` SN.
  - `T`/`H`/`t`/`S` er SN-cifre, og `S` gemmer.
  - `B` er AC-resultatet.
  - Over 9 på T/H/t/S/B giver hverken kvittering eller fejl.
  - [D333] har også `4`, `C`, `D`, `E`, `I`, `N` og `W`.
- **Fejltekster:** `uart read error`, `uart parse error` og `uart unknown command '<c>'`.
- **Faste linjer:** `#0:01;` når tændsekvensen er færdig (`On_Off_Control.c:1093`), og `#0:00;` ved
  sluk (`:1134`). Ellers kommer der kun `left missing` og `left ok - reset` (`:455`, `:469`) og to
  EEPROM-læsefejl (`eeProm_Functions.c:237`, `:246`). `DEBUG_PRINT` er slået fra i 1.0
  (`app.h:61`), så der er ingen boot-linje og ingen reset-årsag.
- **Overrun:** OERR ryddes aldrig. På PIC32 stopper modtagelsen, til OERR ryddes, så én overrun gør
  kommando-UART'en død til næste reset. Det er kode læst og ikke målt.
- **Fund til placering:**
  1. Der er ingen boot-linje og ingen hændelseslinjer (HIL-003). [D333] har `[BOOT]`, `$D` til fri
     tekst (§9.29) og BTL-version (§9.45). **Placeret: §9.44** (`[BOOT]` og `$D` som [D333], ingen
     BTL-linje).
  2. Rammevalideringen er løs (`$1:0X;` udføres). [D333] §9.9 kræver cifre. **Placeret: §9.45.**
  3. OERR ryddes ikke. **Placeret: §9.46** (som [D333], med `[UART] rx-fejl <n>`).
  4. `$2:00;` sætter curInp til 0. **Placeret: §9.47** (0 som over maxInp, og mute-blinket
     følger §9.23).
  5. `$5` opdaterer hverken appData eller EEPROM og kvitterer ugyldige værdier. **Placeret:
     §9.48** (via settings som [D333], 0 = front på linjen, og over 1 ignoreres).
  6. Værdier over 9 afvises tavst, og fejlteksterne er fri tekst. **Placeret: §10.5** (1.0's
     svar bevares).
  7. TX blokerer uden timeout, og der er 10 ms og 50 ms blokerende ventetid. [D333] §9.35 binder
     TX pr. byte. **Placeret: §9.49** (som [D333]).
  8. Hvilke af [D333]'s ekstra kommandoer skal Helios have (`C`, `D`, `E`, `I`, `N`, `W`)?
     **Placeret: §9.50** (alle fire grupper og `M`. `D` er §9.44).
  9. Hvor er interfacet aktivt? [D333] lytter også i fejltilstand. **Placeret: §9.51** ([D333]
     plus hovedmenuen, og bytes uden for vinduet kasseres).
  10. Baudraten: Helios har 115200. Teststativer afhænger af den, så den bevares som parameter.
      **Afgjort af PRD §1:** [D333] kører 230400 (BRG 108 ved 100 MHz), og Helios beholder 115200.
- **Alle 10 fund er placeret.**
- **§4.12 er skrevet** med legacy, FR-1200 (linje, ramme, vindue og kommandotabel), FR-1201
  (`#0:01;`, `#0:00;`) og FR-1202 (`[BOOT] Helios <version>  build …` og `[WDT]` som [D333]).
  **Område 8 er gennemgået.**
- **Åbent:** Hvilke Helios-enheder `$N` kan simulere (§4.6). Formatet på `[BOOT]` er mit forslag
  og venter på Michaels gennemsyn.

### 2026-11-27 (område 7, læst)

Persistens er læst i `eeProm_Functions.c` (uændret siden `v1.0`) og [D333] PRD §4.11 på
`origin/main` (`fe1787d`):

- **Layout (0x50):**
  - 0x00 curInp. 0 gemmes aldrig og ignoreres ved læsning (`:206`, `:340`).
  - 0x01–0x03: startLvl, maxLvl, balance.
  - 0x04: dispMode med simpleView i bit 7.
  - 0x05 irSource og 0x06 avInp.
  - 0x07–0x0A: pcm, dsd (reserveret), dsdLp, digiGain.
  - 0x0B pickup og 0x0C greenBias. 0x0D–0x0F er reserveret, og defaults skriver 0.
  - 0x10–0x15 inpSens[1..6], og 0x16–0x1F skrives til 0.
  - 0x20–0x77: 11 navne à 8 B.
  - 0x80–0x83 SN, 0x84–0x85 boot-tæller (16 bit LE) og 0x86 spændingssetting. Kommentaren
    `:503` siger 0x0D, men den er forkert.
  - Fejlstatus på 0x51:0x00 kaldes aldrig.
  - Chippen ligner en 24LC04B (0x50/0x51, 16 B pages), men det er ikke bekræftet.
- **Første boot:** Er `curInp > 11`, skrives defaults (`On_Off_Control.c:934`).
- **IR i standby (område 5):** ON4 genlæser `curInp` fra EEPROM (`On_Off_Control.c:932`, `:940`),
  så et input valgt i standby overskrives.
- **PRD §4.11** henviser til #1 for layoutet, men det står ikke dér.
- **Fund til placering:**
  1. Boot-tælleren tæller 2 pr. tænding. **Placeret: §9.40** (16 bit, D333 FR-1303).
  2. Der er ingen validering ved indlæsning ud over volumen (`:45-53`). Det dækker også de
     åbne spørgsmål om avInp og IR-kilden. [D333] tolker alt andet end front som bag, og avInp
     som en bitmaske. **Placeret: §9.41** (en ugyldig værdi giver default i RAM).
  3. De to default-veje er forskellige. UART-fabriksreset (`uart_control.c:411`) genindlæser
     hverken navne eller værdier, og ingen af vejene sætter `dsdFilter` eller `curInp` i RAM.
     **Placeret: §9.42** (én vej som [D333] FR-1010/1011).
  4. Skrivefejl ignoreres, og der er ingen persist-guard og ingen read-compare-write ([D333]
     FR-1001, FR-1002).
  5. Blokerende `while (I2C2_IsBusy());` uden timeout (`:99`, `:115`, `:125`).
     **Fund 4 og 5 placeret: §9.43** ([D333]'s driver).
  6. Fejlstatus på 0x51 er død. Skal FR-830 gemme noget, som [D333] gør på 0x100?
  7. Adresse til Auto Standby. Ledigt: 0x0D–0x0F (1.0's restore skriver 0), 0x78–0x7F og
     0x87–0xFF (aldrig skrevet).
     **Placeret: 0x0D i Page0** (0, 0xFF og over 10 betyder fra).
- Fund 6 var allerede afgjort af §9.17, som fjerner skelettet. 0x51 er reserveret.
- **§4.11 er skrevet** med legacy, layouttabellen (FR-1000), FR-1001/1002/1010/1011/1012 og
  §9.40–9.43. De 11 henvisninger til "område 7" er erstattet af adresser. Chipspørgsmålet står i
  §11.6. **Område 7 er gennemgået.**

### 2026-11-27 (område 6, GUI-001)

GUI-001 er skrevet i §3.3 sammen med §9.39 (Michael: én teknik, D333's):

- 1.0 har ikke GUI-001-fejlen, men bruger to teknikker. A er toggleable med `setPressed`, og den
  valgte knap er disabled. B skifter released-image, og den valgte knap er disabled.
- Under A kører `OnShow` handlerne, fordi Legatos `setPressed` kalder `pressedEvent` og
  `releasedEvent`. IR, green bias og pickup har ingen vagt mod det.
- 2.0: Knapperne er ikke toggleable, og released-image skiftes ud fra modellen. Det gælder også
  AV 3/4. Visningen kalder ingen handler.
- Ikke undersøgt: om en disabled knap tegnes anderledes.

### 2026-11-27 (område 6, Pickup og AV)

FR-850, FR-855 og FR-861 er skrevet i §4.10, sammen med §9.37, §9.38, §10.4 og en TIM-række for
pickup-stabilisering (Michael):

- Default for pickup er MM som D333. I 1.0 er den MC. En ugyldig byte giver også MM (§9.37).
  Helios 1.0 havde ikke D333's inkonsistens mellem relæ og menu, fordi begge tester `== MM`.
- Restore bevarer pickup-valget som i 1.0 (§10.4).
- AV-inputs dæmpes i level match som D333 FR-861 (§9.38).
- Legacy-forskelle, der bevares uden beslutning: pickup skrives ved ON med phono- eller
  DAC-modul (D333: kun phono), og AV gemmes ved hver `OnHide`.
- Kilde: D333 PRD på `origin/main` (`fe1787d`).

### 2026-11-27 (område 6, Auto Standby)

FR-815 og FR-816 er skrevet i §4.10, TIM-24 og TIM-25 i §5, og §9.34–9.36 er tilføjet (Michael):

- Menupunktet står nederst til venstre på Exit-rækken. De 10 eksisterende knapper flytter sig ikke.
- +/− gentager ved tryk-hold som D333. Det gælder nu også volSettings (§9.34, FR-303).
- Enhver gyldig IR-frame nulstiller nedtællingen, også én, der kun tænder displayet. Frames,
  der sluges, fordi de har samme toggle, nulstiller ikke (FR-707).
- Overlayet vises med 100 % baglys, og `T_DIM` står stille (§9.35). D333 sætter ikke baglyset.
- Annullering fra menuen kører menu-exit, så mute ikke bliver hængende (§9.36). D333 går
  direkte til action.
- Kilde: D333 `app_standby.c` og `gui_auto_timeout_overlay.c` på `origin/main` (`fe1787d`).

### 2026-11-27 (område 6, SYSTEM ERROR)

FR-830 er skrevet i §4.10, og §9.32 og §9.33 er tilføjet (Michael):

- Kodetabellen følger [D333] FR-530 og er tilpasset Helios' busser. I2C2 har U26, EEPROM og
  DAC-modulet. I2C3 har U16/U20.
- E21/E22 er U16/U20 døde, og E23/E24 er SDA/SCL på I2C3. Det er nyt i forhold til D333.
- E21–E24 låser output-mute på U26 som D333 §9.40 (§9.32). Det virker også ved en låst I2C3.
- E13 bygger på et hjerteslag på U26 byte 1 (`T_E13` = 5 s).
- E31 vises som i D333 (§9.19). Hængelås-ikonet er ikke afgjort.
- To nye hardwarespørgsmål i §11.6: udgangsniveauet ved høj-Z på U16/U20, og om standby er en POR.

### 2026-11-27 (område 6, krav til skærme)

Kravene til skærmkatalog og skift er skrevet i §4.10 (Michael):

- FR-800, FR-810, FR-811 og FR-812 følger [D333] med Helios' forskelle: ingen monitor og
  ventilator, Green bias, AV på input 3 og 4, to AC-fejlskærme og `T_DIM` på 8 s.
- FR-880 (300 ms ved skærmskift) og FR-881 (fade) er Helios-specifikke. D333 har ingen af dem.
- Fade blokerer ikke i 2.0 (§9.31).
- FR-882 (menu) henviser til FR-314 for mute. D333 løser det med FR-316 i `app_audio_ctrl`.

### 2026-11-27 (område 6, legacy)

Legacy-afsnittet i §4.10 er skrevet (Michael godkendte udkastet):

- Skærmkatalog med 23 skærme (`le_gen_init.h:40-62`), drift-skærme og menu ind og ud
  (`app.c:107-125`), display-modes, omdøbning og fade.
- Det er præciseret, at kun off sætter `dispSleepActiveFlg` (`screen_Action.c:345` er
  udkommenteret). Dim tæller derfor som dæmpet over for IR.
- Fade (40 × 50 ms) er tilføjet i §5 som TIM-xx.
- Undermenuernes egen adfærd er ikke læst. Den er dækket af område 3–5 eller hører til
  område 7.

### 2026-11-27 (område 6, fund placeret)

De 8 fund fra log-posten "område 6, læst" er placeret (Michael):

1. **Format-string:** §9.28. Inputnavne er data, `%` er et almindeligt tegn, og tastaturet er
   uændret.
2. **Buffere:** NFR-021 er udvidet. `setFromCStr` klipper og skriver ingen terminator
   (`legato_fixedstring.c:193-205`), så der er intet overløb uden fund 1. Display-modeteksterne
   er op til 8 tegn ("AUTO OFF"), ikke 4.
3. **Genereret kode:** NFR-015 og §9.29 følger [D333] rebuild: `touch_bridge.c` med en egen
   `SYS_INP`-lytter. Touch-genopretningen i `DRV_TOUCH_STATE_ERROR` (#60, #103) er den eneste
   sanktionerede håndrettelse med en genindsættelsesprocedure.
4. **§3.2:** Linjen om volumenskrivningen er rettet. Den sker i `updateActionScreen` og
   `updateSimpleViewScreen`.
5. **Pickup og AV:** Noteret som legacy i §4.10. Kravene skrives sammen med [D333] FR-850 og
   FR-861.
6. **Død overlay-logik:** §9.30.
7. **Mute-krydset:** Observation under NFR-020. Skærmtjekket hører hjemme i GUI-funktionen.
8. **Fonte:** GUI-002 er skrevet ind i §3.3 med en fonttabel. Alle dynamiske kilder er dækket
   (inputnavne bruger `Avenir18` og `Avenir64`). GUI-001 er ikke undersøgt.

### 2026-11-27 (D333-referencer)

- D333-referencerne i PRD'en er sammenlignet med D333 `origin/main` (`fe1787d`, 2026-11-17).
  Grundlaget var det lokale checkout (`d0cde33`, 2026-10-28), som område 1–5 blev læst fra.
- Alle refererede moduler og filer findes. Ingen FR-, TIM- eller §9-numre er flyttet. D333 har
  tilføjet FR-530, FR-850/860/861 og §9.40–9.45.
- **Rettet i PRD:** §9.19 havde "en NACK eskalerer straks", men siden D333 #408 bruger NACK
  budgettet, og kun `ERR_PARAM` eskalerer straks. §8 har nu bænkstatus i stedet for
  "_tjekkes_": Auto Standby (#115, 2026-06-30), `svc_power` (#52, 2026-06-25), IR-kilde (#56,
  2026-06-30). Superloopen har intet eget issue og er kun bevist indirekte gennem #52–#56.

### 2026-11-27 (område 6, læst)
- **Beslutninger (PRD §1 og §4.10):** D333 læses fra `origin/main`. `SN_SET` udgår.
  `errorDisplay` bliver SYSTEM ERROR-skærm efter D333 FR-530 (fx I²C-busfejl), med en
  kodetabel til Helios.
- **Fund, der venter på Michaels placering i §9 eller §10 (kode læst):**
  1. **Format-string:** Et inputnavn med `%` fra tastaturet (`Screen_Qwerty_Keypad.c:36`) bruges
     som format i `sprintf(cCharBuffer2, inpNames[...])` (`Screen_SimpleView.c:51`, `:92`,
     `uart_control.c:308`). Det er udefineret adfærd og kan skrive ud over `cCharBuffer2[16]`.
  2. **NFR-021:** Buffer mod kapacitet:
     - `Screen_SimpleView.c`: 8 mod 16 (`:10`/`:91`) og 9 mod 16 (`:12`/`:160`).
     - `Screen_Qwerty_Keypad.c`: 9 mod 16 (`:29-30`/`:272-273`).
     - `legatoCharBuffer`: 8 mod 16 (`ui_globals.c:24`, `screen_Action.c:758`,
       `Screen_SimpleView.c:101`).
     - Ok: inputnavne, Fs og FW (16 mod 16) og SN (8 mod 6).
  3. **MCC-001:** De genererede filer `le_gen_harmony.c:114-130` (touch-hooks til
     volumen-repeat) og `drv_touch_controller.c:403-415` (I²C1-genstart og
     `ActionTouch_OnError` ved touch-fejl) er rettet i hånden. En regenerering fjerner
     rettelserne. NFR-015 nævner kun `tasks.c`.
  4. **§3.2 linje 108 er forkert:** Volumenskrivningen over I²C sker i `updateActionScreen`
     (`screen_Action.c:1394-1404`), ikke i `ActionScreen_VolumeUiPump`.
  5. **Huller:**
     - **Pickup MM/MC:** Ved et skift sættes niveauet til 0, valget gemmes, U26 sættes, og der
       vises en progressbar til 100 med et trin hver 250 ms, i alt 25 s
       (`Screen_Pickup_Selection.c:49-74`).
     - **AV-skærmen:** Ingen, input 3 og 4 er toggles, og valget gemmes på `OnHide`
       (`Screen_AV_Setup.c`).
     - Ingen af de to står i PRD'en.
  6. **Død logik:**
     - `prevStateForOverlay` tildeles aldrig, så overlayenes `OnHide` sætter tilstanden til
       `INIT` (`Screen_SimpleView.c:256-272`, `app.c:84`). Den nye skærms `OnShow` overskriver
       den.
     - `uiOverlayActive` sættes aldrig til 1.
     - `filterSimpleView_OnShow` sætter `APP_STATE_IDLE` (`:179`), men de to andre overlays
       gør ikke.
  7. **NFR-020:** `updateSimpleViewScreen` skriver mute-krydset hvert tik uden at tjekke den
     aktuelle skærm (`Screen_SimpleView.c:28-31`). Kaldet er dog gated i `app.c:205`.
  8. **GUI-002 (ikke færdigt):** De fleste fonte har 0x20–0x7E og 0xC5–0xD8. `avenir48` har kun
     0x20 og 0x23–0x5A, så den mangler Æ, Ø, Å og `! ' ^ _ ~`, som tastaturet har. Det er ikke
     fastslået, hvilken font de dynamiske inputnavne bruger (`fontList`,
     `le_gen_stringtable.c:378`).
- **Adfærd, der skal ind i §4.10 (kode læst):**
  - **Display-modes:** 100/75/50/25 % giver PWM 100/60/40/15. Dim og off giver 100 % ved
    aktivitet og derefter 15 % eller 0 efter T_DIM (`Screen_Display_Setup.c:14-45`,
    `screen_Action.c:336-369`).
  - **Skærmskift:** Baglyset står, og `setDisplayIntensity()` kaldes 300 ms efter `OnShow` på
    action og simple view (`Display_Backlight.c:38-46`, `screen_Action.c:769-775`). Touch på
    simple view slukker baglyset før skiftet (`Screen_SimpleView.c:78-86`).
  - **Menuen:** Baglys 100 %. Knapperne Digital og Pickup skjules uden modul
    (`Screen_Main_Menu.c:65-77`). Green bias er altid synlig.
  - **Omdøbning:** 8 tegn. Tastaturet har A–Z, ÆØÅ, cifre og symboler. Navnet gemmes ved OK
    (`Screen_Qwerty_Keypad.c`).
  - **Fade:** Fade ind og ud tager 40 × 50 ms og blokerer (`Display_Backlight.c:4-24`, kaldt
    fra `On_Off_Control.c:919`, `:1059`).

### 2026-11-27 (område 5, krav)
- Krav til 2.0 i §4.9: FR-700–705 efter D333, FR-706 (power og opvågning) og FR-707
  (display slukket eller dæmpet) er Helios-specifikke. Kravet om en UART-hændelseslinje pr.
  IR-kommando er lagt videre til område 8. Område 5 er gennemgået.

### 2026-11-27 (område 5)
- Legacy i §4.9: dekoder, toggle og hold, kommandotabel, overlays, display-wake, standby og
  opstart samt IR-kilde. D333's løsning er bænkbevist (#56, #162, #280 del B).
- §2 er rettet: `IR_RC5` er RH3, og RH11 er `IR_SOURCE`. Kommentaren i
  `On_Off_Control.c:1162` er forkert.
- **Beslutninger:**
  - §9.20: IR samples i CN-ISR'en som D333, med RC5X og Helios' tider. Tiderne bevises på
    bænken med en Arduino som IR-kilde. §9.12 og NFR-010/011 er rettet til D333's bus-guard.
  - §9.21: I standby tæller kun 12/123.
  - §9.22: Under opstart virker kun sluk (12/124) fra ON4.
  - §9.23: Et inputvalg, der intet ændrer, gør intet.
  - §9.24: Overlay-timeren genstartes ved tryk.
  - §9.25: IR blokerer ikke.
  - §9.26: Død kode, og kode 21 ignoreres.
  - §9.27: IR-kilden gemmes straks som D333 FR-705. Først placeret i §10.4 under den forkerte
    antagelse, at D333 ingen IR-kilde har.

### 2026-11-27 (område 4, krav)
- Krav til 2.0 i §4.6: FR-203, FR-400–406 efter [D333], FR-407 (moduldetektion) og FR-410
  (green bias). FR-106 har ingen fejl-triggere fra DAC/U26. Område 4 er gennemgået.
- **Beslutninger:**
  - DAC-init i ON5 blokerer med watchdog-strobe som [D333] (undtagelse i NFR-011).
  - Et fejlet digitalt skift prøves igen som [D333] §9.28 (§9.19).
- §5 har seks nye TIM-rækker, og §8 har rækker for DAC-modul (bænkbevist, D333 #53), retry
  (host-verificeret, D333 #234) og green bias.

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
