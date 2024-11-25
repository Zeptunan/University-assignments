Bildmatchning
=============

- Ungefärligt antal timmar spenderade på labben (valfritt):
 Ingen aning, kanske 4-5 dagar. Osäker på antal timmar per dag

- Vad är tidskomplexiteten på "slow.cpp" och din implementation av "fast.cpp",
  uttryckt i antalet bilder (n).

slow: O(n²) – eftersom varje bild jämförs med varje annan bild, 
vilket innebär en kvadratisk tillväxt i antalet operationer beroende på antalet bilder (n).
fast: O(n) – eftersom varje bild bearbetas en gång för att beräkna dess sammanfattning och sedan 
lagras eller jämförs med andra i en hash-struktur, vilket gör att programmet växer linjärt med antalet bilder.


- Hur lång tid tar det att köra "slow.cpp" respektive "fast.cpp" på de olika
  datamängderna?
  Tips: Använd flaggan "--nowindow" för enklare tidsmätning.
  Tips: Det är okej att uppskatta tidsåtgången för de fall du inte orkar vänta
  på att de blir klara.
  Tips: Vid uppskattning av körtid för "slow.cpp" är det en bra idé att beräkna
  tiden det tar att läsa in (och skala ner) bilderna separat från tiden det tar att
  jämföra bilderna. (Varför?)

|--------+-----------+----------+----------|
|        | inläsning | slow.cpp | fast.cpp |
|--------+-----------+----------+----------|
| tiny   |   92ms    |   183ms  |  165ms   |
| small  |   707ms   |   891ms  |  888ms   |
| medium |   3259ms  |   4592ms |  3444ms  |
| large  |   76122ms |  544617ms|  76291ms |
|--------+-----------+----------+----------|


- Testa olika värden på "summary_size" (exempelvis mellan 6 och 10). Hur
  påverkar detta vilka dubbletter som hittas i datamängden "large"?

tiden det tar för programmet att köras ökar lite och antal dubletter som hittas minskar.
När summary_size ökar, bevaras fler detaljer när nerskalning sker vilket gör att det tar
längre tid att bearbeta bilderna. När fler detaljer bevaras blir det enklare att skilja 
bilderna åt. 

- Algoritmen som implementeras i "compute_summary" kan ses som att vi beräknar
  en hash av en bild. Det är dock inte helt lätt att hitta en bra sådan funktion
  som helt motsvarar vad vi egentligen är ute efter. Vilken eller vilka
  egenskaper behöver "compute_summary" ha för att vi ska kunna lösa problemet i
  labben? Tycker du att den givna funktionen uppfyller dessa egenskaper?

De egenskaper som compute_summary behöver ha är:
Den måste kunna skala ner en bild på ett sätt som bevarar tillräckligt med relevant information.
Den ska kunna jämföra ljusstyrkan mellan närliggande pixlar för att skapa en representation av bildens horisontella 
och vertikala mönster. Denna representation hjälper till att skilja mellan bilder med olika ljusstyrkefördelningar.
Den uppfyller dessa krav men resultatet kan påverkas av valet av summary_size.
mindre storlekar bevarar mindre detaljer, medan större storlekar kan vara mer nogranna men också långsammare. 
Själva jämförelsen mellan bilder sker dock senare, när vi matchar dessa sammanfattningar (hash-värden) i vår unordered_map.

//TODO: Komplettering. "för att hitta likheter mellan bilder" 
Hur då? Är det här en del av `compute_summary`? 

- Ser du några problem med metoden för att se om två bilder är lika dana?
  Föreslå en alternativ metod för att hitta bilder som är lika. Vad har
  ditt/dina förslag för för- och nackdelar jämfört med det som föreslås i
  labben? Fokusera exempelvis på vilka typer av skillnader i bilder som
  hanteras, eller vilken tidskomplexitet som kan uppnås. Ditt förslag behöver
  inte vara snabbare än det som föreslås i labben, men du ska komma på
  åtminstone en fördel med din metod.

Just nu jämför vi ljusstyrka som kan leda till fel om bilderna är olika färger men har liknande kontrast.
Man hade istället kunna jämföra bildernas RGB-värde för att uppnå mer korrekta svar. 
Det gör att vi får mer korrekta jämförelser men ökar också tidskomplexiteten till en kvadratisk 
tidskomplexitet O(n²) eftersom vi då måste jämföra varje bild mot alla andra bilder i datamängden 
och varje jämförelse skulle kräva att vi kontrollerar varje enskild pixels färginformation istället för 
bara ljusstyrka. 

//TODO: Komplettering. 
Ja den kommer antagligen öka, men varför ökar tidskomplexiteten? Vad jämför ni varje bild emot?
