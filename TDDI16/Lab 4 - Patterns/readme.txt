Mönsterigenkänning
==================

- Ungefärligt antal timmar spenderade på labben (valfritt):


- Vad är tidskomplexiteten (i ordo-notation) för värstafallstiden av
  programmen som en funktion av N (antal punkter). Ge en kort motivering.

  Matchar brute-lösningen sitt värstafall i praktiken, eller har den ett
  medelfall som är bättre?

brute: Värstafallel sker när programmet går igenom alla möjliga kombinationer av fyra punkter och för varje 
punkt kontrollerar om punkterna ligger på en linje, det här ger en tidskomplexitet på O(N⁴) eftersom vi har 
4 loopar som alla har en linjär tidskomplexitet. 
Medelfallet är bättre med en tidskomplexitet på O(n³)

fast: Värstafallet för fast är O(n² log n). det mest tidskrävande i fast är att sortera punkterna som sker på
O(n log n) eftersom den använder sig av quicksort, men värsta fallet för quicksort påverkar inte tidskomplexiteten 
eftersom sort använder sig av heapsort när quicksort tar för långt tid. resten av operationerna inom ytterloopen
är antingen konstanta eller linjära. så med ytterloopens tidskomplexitet blir totala tidskomplexiteten O(n) * O(n log n) = O(n² log n)


- Fyll i tabellen nedan med riktiga körtider i sekunder när det känns
  vettigt att vänta på hela beräkningen.
  Ge uppskattningar av körtiden (baserat på tidskomplexiteten)
  i övriga fall.
    
      N       brute (s)    sortering (s)
 ------------------------------------
    150       0.080        0.010 
    200       0.238        0.019
    300       0.644        0.038
    400       1.591        0.059
    800       13.300       0.219
   1600       102.966      0.901                   
   3200       1647         3.834                uppskattade tider för brute härifrån med formel T(N2) = T(N1) * (N2/N1)⁴
   6400       26359        16.422
  12800       421748       70.206


- Energianvändning

  Antag att du använder mönsterigenkänningsprogrammet för att analysera
  data från en kamera. Kameran sitter i en byggnad och tar en bild
  på stommen av byggnaden var 30:e minut. Bilden förbehandlas sedan
  lite, innan punkter som representerar stommen skickas till
  mönsterigenkänningsprogrammet. Hittas inte tillräckligt många raka
  linjer så betyder det att något håller på att gå sönder, och
  att byggnaden behöver noggrannare inspektion.

  Hur mycket energi sparar du på ett år om du använder din snabbare
  sorteringslösning i stället för brute-lösningen? Du kan anta följande:
  - Systemet körs 24/7 under hela året.
  - Inget annat körs på det här systemet.
  - Systemet drar 8 W när det inte gör något (idle)
  - Systemet drar 36 W när det arbetar (med 1 kärna)
  - Räkna med att ditt program körs var 30:e minut (= 2 gånger/timme)
  - För- och efterbehandling är snabba, så vi kan bortse från dem
  - Indata till programmet innehåller ca 6400 punkter
  - Det är inte skottår (= 365 dagar)

  Att jämföra med drar en kombinerad kyl/frys ca 200 kWh per år
  (enligt Energimyndigheten).
 
  Kom ihåg: energi mäts ofta i kWh, vilket är:
   energi (kWh) = effekt (kW) * tid (h)

  Tips: ett sätt att räkna på är att först räkna förbrukningen av
  ett system som inte gör något på ett helt år, sedan lägga till
  den extra förbrukningen (36 W - 8 W = 28 W) för tiden som systemet
  är aktiv.

  (Siffrorna är löst baserade på en Intel i9-9900K, vi räknar bara på
  CPU:n för enkelhets skull, besparingarna blir sannolikt större om
  vi räknar på större delar av systemet, även om andra komponenter
  också drar ström i "idle".)


Förbrukning av brute på ett år: 315.36 kWh
uppskattad körtid för brute med 6400 inputs = 26359s = 7.322 timmar
totalt aktiv tid per dag = 48 x 7.322 = 351.456 timmar
total aktiv tid per år = 24 x 365 = 8760h 
extra energiförbrukning = 28 x 8760 = 245.28 kWh 
basförbrukning (idle) = 8 x 8760 = 7080 Wh = 70,08 kWh
total förbrukning = 70.80 + 245.28 = 315.36 kWh 

Förbrukning av sortering på ett år: ? kWh
körtid med 6400 inputs för fast = 16.422s = 0.00456 timmar
total aktiv tid per år = 0.00456 x 17520 = 79.7952 timmar
extra energiförbrukning = 28 x 79.7952 = 2234.266 wH = 2.234 kWh
basförbrukning (idle) = 70.08 kWh
total förbrukning = 70.08 + 2.234 = 72.314 kWh

Skillnad: 315.36 - 72.314 = 243.046 kWh/år 

