# OP
Objektinis Programavimas

## Naudojimosi instrukcija

1. Atsisiųskite (arba nuklonuokite) šį projektą į savo kompiuterį.
2. Atidarykite terminalą tame aplanke.
Pvz. C:\Users\Public\Documents\GitHub\OP2
3. Programos paleidimas (įveskite į terminalą): 
mkdir build
cd build
cmake ..
cmake --build .
cd Debug
main.exe
4. Vykdykite programos nurodymus terminale:
   - Pasirinkite veiksmą (failų generavimas, duomenų įvedimas, skaitymas iš failo ir t.t.).
   - Pasirinkite rūšiavimo būdą.
   - Įveskite failo pavadinimą, jei reikia.
5. Rezultatai bus išsaugoti į `vargsai.txt` ir `kietakai.txt` failus.

## Kompiliatoriaus optimizavimo flag'ų (O1, O2, O3) įtaka

Eksperimentas atliktas su komanda:
- `g++ -O1 -o main_O1 main.cpp Studentas.cpp`
- `g++ -O2 -o main_O2 main.cpp Studentas.cpp`
- `g++ -O3 -o main_O3 main.cpp Studentas.cpp`

Testuota su failais: studentai100000.txt ir studentai1000000.txt  
Sistema: Intel i9-14900HX, 32GB RAM, SSD 1000GB, Windows 11

| Optimizavimo lygis | studentai100000.txt rūšiavimo trukmė | studentai1000000.txt rūšiavimo trukmė |
|--------------------|--------------------------------------|---------------------------------------|
| -O0 (be optimiz.)  | 0.276829 s                               | 3.32324 s                                |
| -O1                | 0.102687 s                               | 1.25678 s                                |
| -O2                | 0.09735 s                               | 1.22385 s                                |
| -O3                | 0.104992 s                               | 1.23305 s                                |

**Išvada:**  
Kompiliatoriaus optimizavimo flag'ai (-O1, -O2, -O3) žymiai pagreitina rūšiavimo vykdymą.  
Didžiausias pagreitėjimas matomas prie -O2.  
Rekomenduojama naudoti bent -O2 galutiniam programos variantui.


## Testavimas atliekamas su tais pačiais failais iš 100000, 1000000 įrašų.
Sistemos parametrai:
Intel i9-14900HX
32GB RAM
SSD 1000GB

Duomenų apdorojimas:

3 Strategija: Bendro studentai konteinerio skaidymas (rūšiavimas) į du naujus konteinerius, naudojant "efektyvius" darbo su konteineriais metodus.

studentai100000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.658439 s  |  0.037274 s  |  0.411755 s  | 
| list |  0.825068 s  |  0.019493 s  |  0.460547 s |
| deque  |  0.612626 s  |   0.071794 s  |  0.572771 s  |
| class  |  0.63989 s  |   0.04844 s  |  0.276829 s  |

studentai1000000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  6.51211 s  |  0.389969 s  |  5.55069 s  | 
| list  |  8.25015 s  |  0.178532 s |  6.76464 s  |
| deque  |  6.24909 s  |  0.73808 s  |  7.58263 s  |
| class  |  6.35175 s  |  0.485685 s  |  3.32324 s  |

Perdarius viską iš struct į class žymiai pagreitėjo rūšiavimas didėjimo tvarka, o skaitymas ir skirstymas labai nepasikeitė.