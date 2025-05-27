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
   - Pasirinkite rūšiavimo būdą ir strategiją.
   - Įveskite failo pavadinimą, jei reikia.
5. Rezultatai bus išsaugoti į `vargsai.txt` ir `kietakai.txt` failus.

Testavimas atliekamas su tais pačiais failais iš 100000, 1000000 įrašų.
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


studentai1000000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  6.51211 s  |  0.389969 s  |  5.55069 s  | 
| list  |  8.25015 s  |  0.178532 s |  6.76464 s  |
| deque  |  6.24909 s  |  0.73808 s  |  7.58263 s  |

Palyginus visas šias strategijas galima teigti, kad 3 strategija yra greičiausia, o antra strategija nors ir sutaupo atminties, bet didėjant studentų skaičiui programos veikimo laikas pradeda drastiškai ilgėti.

![3 Strategija](nuotraukos/strategija.png)