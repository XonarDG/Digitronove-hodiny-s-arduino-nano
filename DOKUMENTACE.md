<H1>Digitronové hodiny</H1>
  <H5>Vojtěch Pindur</H5>


V mém ročníkovém projektu jsem se rozhodl udělat Digitronové hodiny. V tomto dokumentu budu popisovat jak projekt funguje a jaké řešení jsem vybral a proč.

<H2>Popis projektu</H2>
Cílem projektu jsou funkční, jednoduché a relativně přesné Digitronové hodiny za použití Mikroprocesoru a modulu Přesného času.

<H2>Stručný popis řešení</H2>
Řešení je samozřejmě více, já popíšu mnou vybrané a zhotovené.
Jako mikrokontrolér použiju desku Arduino Nano s mikroprocesorem ATmega 328.  Dále používám modul přesného času DS3231 (RTC modul). Digitrony Tesla ZM1020 které jsou dále ovládány BCD dekodéry Tesla MH74141 a vysoké napětí vyžadované Digitrony je dodáváno Step-Up měničem koupeného z Ebay. Mé řešení nepoužívá multiplexování.

<H2>Obhájení řešení</H2>
<ol>
  <li>
    <b>Výběr mikrokontroléru</b>
      <ol>
        <li>
            Má pro můj projekt dostatek IO
        </li>
        <li>
            Jednoduše se usazuje na plošném spoji
        </li>
        <li>
            Jednoduše se programuje (přes USB)
        </li>
      </ol>
  </li>
  <br>
  <li>
    <b>Výběr RTC</b> <i>(modulu přesného času)</i>
      <ol>
        <li>
            Mám ho po ruce
        </li>
      </ol>
  </li>
  <br>
  <li>
    <b>Výběr Digitronů</b> <i>(zobrazovačů)</i>
      <ol>
        <li>
            Měl jsem je po ruce
        </li>
        <li>
            Jsou dělané do patic <i>(zjednodušuje to jejich upevnění)</i>
        </li>
        <li>
            Číslice jsou na jejich velikost relativně velké
        </li>
      </ol>
  </li>
  <br>
  <li>
    <b>Výběr BCD dekodérú</b>
      <ol>
        <li>
            Měl jsem je po ruce
        </li>
        <li>
            Dokážou snést vyšší napětí vyžadované Digitrony
        </li>
      </ol>
  </li>
  <br>
  <li>
    <b>Nepoužití Multiplexování</b>
      <ol>
        <li>
            Cílem projektu je udělat funkční a jednoduché hodiny (zdálo se mi že multiplexování je již trochu pokročilejší, navíc jsem se rozhodl že napoprvé bych neměl zkoušet moc nových věcí zároveň)
        </li>
      </ol>
  </li>
</ol>

<H2>Řešení</H2>

Zapojení je celkově dost jednoduché. Mikrokontrolér má pro každý BCD dekodér 4 výstupy A, B, C, D. V tomto se skrývá hlavní nevýhoda zapojení bez použití multiplexování, protože jenom BCD dekodéry samotné zabírají 16 výstupů. Dále je mikrokontrolér připojen k RTC přes I2C interface, který naštěstí používá
jen 2 výstupy. No a další zapojení už je vlastně jenom od každého BCD dekodéru k individuálním anodám digitronů, propojení všech VCC s 5v kolejí zakoupeného zdroje, propojení všech GND a propojení všech katod digitronů přes proud omezovací rezistory.
<br>
<H4>Kód</H4>
      
Co se kódu týče tak ten jsem poslal již před tím, nicméně ho raději pošlu ještě jednou společně s touto prací. Kód má několik fází :

<ol>
  <li>
    <b>Inicializace</b> (definice všech výstupů, deklarace zkratek, zahájení komunikace s RTC modulem, nastavení výstupů a nastavení všech výstupů pro BCD dekodéry na 0)
  </li>
  <li>
    <b>Čtení času z RTC a převod na jednotlivé číslice</b> (hlavně použitím   % 10, tedy zbytek po dělení desítkou)
  </li>
  <li>
    <b>Výstup pro BCD dekodéry</b> (s použitím metody s prvkem switch kde jsou podle vstupů, tedy pořadí digitronu a čísla které má být zapsáno, nastavují výstupy pro BCD dekodéry)
  </li>
</ol>
<br>

<H2>Cena a projektu</H2>
Je důležité mít na paměti to, že digitrony, jakožto technologie, už nejsou používány minimálně takových 30 až 40 let. Byly nahrazeny modernějšími VFD displeji, a později 7 segmentovými LED zobrazovači. Z toho vyplývá že digitrony, a ani jejich drivery, už dnes jen těžko seženete na e-shopech jako GMe.
<br>

<ol>
  <li>
    Arduino Nano - 190 kč
  </li>
  <li>
    RTC modul - 108 kč
  </li>
  <li>
    MH74141 nebo K155ID1 - ceny na ebay se pohybují od 64 kč za kus až 100 kč za kus. Je důležité si vybrat důvěryhodného prodejce aby vám nepřišly padělky.
  </li>
  <li>
    Digitrony - jsou asi nejdražší částí projektu. Digitronů existuje nespočet různých velikostí a druhů. Nicméně na ebay jsou zdaleka nejpopulárnější ruské digitrony. Alternativou za mé české Tesla ZM1020 jsou ruské IN-12 nebo IN-12B. - Ceny se pohybují od 100 kč a můžou se vyšplhat až do tisíců za kus. Pokud byste kupovali IN-12(B) tak vás to asi vyjde zhruba nějakých 850 až 1000 kč za 4 kusy s dopravou i daněmi.
  </li>
</ol>
