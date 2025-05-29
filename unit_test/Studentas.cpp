#include "Studentas.h"
#include "Mylib.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Vector.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <direct.h>

using namespace std;
using namespace std::chrono;

char rikiavimas; // Globalus rikiavimo būdas

// Konstruktoriai/destruktorius
Studentas::Studentas() : Zmogus(), nd_(), egz_(0) {}
Studentas::Studentas(const std::string& var, const std::string& pav, const Vector<int>& nd, int egz)
    : Zmogus(var, pav), nd_(nd), egz_(egz) {}
Studentas::~Studentas() {}

// Copy constructor
Studentas::Studentas(const Studentas& other)
    : Zmogus(other.var_, other.pav_), nd_(other.nd_), egz_(other.egz_),
      cachedVidurkis(other.cachedVidurkis), cachedMediana(other.cachedMediana) {}

// Move constructor
Studentas::Studentas(Studentas&& other) noexcept
    : Zmogus(std::move(other.var_), std::move(other.pav_)), nd_(std::move(other.nd_)), egz_(other.egz_),
      cachedVidurkis(other.cachedVidurkis), cachedMediana(other.cachedMediana) {}

// Copy assignment
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        var_ = other.var_;
        pav_ = other.pav_;
        nd_ = other.nd_;
        egz_ = other.egz_;
        cachedVidurkis = other.cachedVidurkis;
        cachedMediana = other.cachedMediana;
    }
    return *this;
}

// Move assignment
Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        var_ = std::move(other.var_);
        pav_ = std::move(other.pav_);
        nd_ = std::move(other.nd_);
        egz_ = other.egz_;
        cachedVidurkis = other.cachedVidurkis;
        cachedMediana = other.cachedMediana;
    }
    return *this;
}

// Įvesties operatorius
std::istream& operator>>(std::istream& in, Studentas& s) {
    s.nd_.clear();
    in >> s.var_ >> s.pav_;
    int n;
   
    for (int i = 0; i < 15; ++i) { 
        if (!(in >> n)) break;
        s.nd_.push_back(n);
    }
    in >> s.egz_;
    s.cachedVidurkis = -1;
    s.cachedMediana = -1;
    return in;
}

// Išvesties operatorius
std::ostream& operator<<(std::ostream& out, const Studentas& s) {
    out << s.var_ << " " << s.pav_ << " ";
    for (int n : s.nd_) out << n << " ";
    out << s.egz_;
    return out;
}

// Medianos funkcija
double Mediana(const Vector<int>& vec) {
    if (vec.empty()) return 0.0;
    Vector<int> sortedVec = vec;
    sort(sortedVec.begin(), sortedVec.end());
    int n = sortedVec.size();
    if (n % 2 == 0) {
        return (sortedVec[n / 2 - 1] + sortedVec[n / 2]) / 2.0;
    } else {
        return sortedVec[n / 2];
    }
}

// Studentas metodai
double Studentas::galutinisVidurkis() const {
    if (cachedVidurkis >= 0) return cachedVidurkis;
    if (nd_.empty()) return 0.0;
    double suma = 0.0;
    for (int n : nd_) suma += n;
    double vid = suma / nd_.size();
    cachedVidurkis = 0.4 * vid + 0.6 * egz_;
    return cachedVidurkis;
}

double Studentas::galutinisMediana() const {
    if (cachedMediana >= 0) return cachedMediana;
    if (nd_.empty()) return 0.0;
    double med = Mediana(nd_);
    cachedMediana = 0.4 * med + 0.6 * egz_;
    return cachedMediana;
}

void Studentas::skaiciuotiCache() const {
    galutinisVidurkis();
    galutinisMediana();
}

// Pagalbinė funkcija įvesties laukui išvalyti
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Atsitiktinio vardo generavimas 
string generuotiVarda() {
    return "Vardas";
}

// Atsitiktinės pavardės generavimas
string generuotiPavarde() {
    return "Pavarde";
}


// Studentų nuskaitymas iš failo
bool skaitymas(Vector<Studentas>& studentai, const string& failoPav) {
    ifstream inFile(failoPav);
    if (!inFile) {
        cerr << "Nepavyko atidaryti failo: " << failoPav << endl;
        return false;
    }

    string line;
    getline(inFile, line); // Praleidžiam antraštę
    studentai.clear();
    while (getline(inFile, line)) {
        if (line.empty()) continue; // Praleidžiam tuščias eilutes

        istringstream iss(line);
        string vardas, pavarde;
        if (!(iss >> vardas >> pavarde)) {
            cerr << "Klaida skaitant studento duomenis" << endl;
            continue;
        }
        Vector<int> nd;
        int value;
        while (iss >> value) {
            nd.push_back(value);
        }
        if (nd.size() < 1) continue; // Turi būti bent 1 skaičius (egzaminas)
        int egz = nd.back();
        nd.pop_back();
        studentai.emplace_back(vardas, pavarde, nd, egz);
    }

    return true;
}

// Studentų spausdinimas
void spausdinti(const Vector<Studentas>& studentai, ostream& out) {
    out << left << setw(15) << "Vardas" << setw(20) << "Pavarde"
        << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << "---------------------------------------------------------------------" << endl;

    for (const auto& student : studentai) {
        out << left << setw(15) << student.vardas()
            << setw(20) << student.pavarde()
            << setw(20) << fixed << setprecision(2) << student.galutinisVidurkis()
            << setw(20) << fixed << setprecision(2) << student.galutinisMediana()
            << endl;
    }
}

// Studentų rikiavimas pagal pasirinktą kriterijų
void rikiuotiStudentus(Vector<Studentas>& studentai, char rikiavimas) {
    for (auto& s : studentai) s.skaiciuotiCache(); // Optimizacija!
    if (rikiavimas == 'v') {
        sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.vardas() < b.vardas();
        });
    } else if (rikiavimas == 'p') {
        sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.pavarde() < b.pavarde();
        });
    } else if (rikiavimas == 'a') {
        sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinisVidurkis() < b.galutinisVidurkis();
        });
    } else if (rikiavimas == 'm') {
        sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinisMediana() < b.galutinisMediana();
        });
    }
}

// Studentų įvedimas ranka
void ivestiStudentus(Vector<Studentas>& studentai) {
    char continueInput;
    do {
        string vardas, pavarde;
        Vector<int> nd;
        int egz;

        cout << "Iveskite studento varda: ";
        cin >> vardas;
        cout << "Iveskite studento pavarde: ";
        cin >> pavarde;

        cout << "Ar norite generuoti atsitiktinius balus? (t - taip, n - ne): ";
        char pasirinkimas;
        while (!(cin >> pasirinkimas) || (pasirinkimas != 't' && pasirinkimas != 'n')) {
            clearInput();
            cout << "Neteisinga ivestis. Bandykite dar karta: ";
        }

        if (pasirinkimas == 't') {
            int n = 15;
            nd.resize(n);
            for (int j = 0; j < n; j++) {
                nd[j] = rand() % 10 + 1;
            }
            egz = rand() % 10 + 1;
        } else {
            char continueNdInput;
            do {
                int grade;
                cout << "Iveskite namu darbo ivertinima: ";
                while (!(cin >> grade) || grade < 0 || grade > 10) {
                    clearInput();
                    cout << "Neteisinga ivestis. Bandykite dar karta: ";
                }
                nd.push_back(grade);

                cout << "Ar norite prideti dar viena namu darba? (t - taip, n - ne): ";
                while (!(cin >> continueNdInput) || (continueNdInput != 't' && continueNdInput != 'n')) {
                    clearInput();
                    cout << "Neteisinga ivestis. Bandykite dar karta: ";
                }
            } while (continueNdInput == 't');

            cout << "Iveskite studento egzamino ivertinima: ";
            while (!(cin >> egz) || egz < 0 || egz > 10) {
                clearInput();
                cout << "Neteisinga ivestis. Bandykite dar karta: ";
            }
        }

        studentai.emplace_back(vardas, pavarde, nd, egz);

        cout << "Ar norite prideti dar viena studenta? (t - taip, n - ne): ";
        while (!(cin >> continueInput) || (continueInput != 't' && continueInput != 'n')) {
            clearInput();
            cout << "Neteisinga ivestis. Bandykite dar karta: ";
        }
    } while (continueInput == 't');
}

// Studentų rikiavimas ir išvedimas į failus
void sortAndOutputStudents(Vector<Studentas>& studentai) {
    // 1. Skirstymas į grupes
    auto start_split = high_resolution_clock::now();

    Vector<Studentas> vargsai, kietakai;
    for (const auto& student : studentai) {
        if (student.galutinisVidurkis() < 5.0) {
            vargsai.push_back(student);
        } else {
            kietakai.push_back(student);
        }
    }

    cout << "Vargsai kiekis: " << vargsai.size() << endl;
    cout << "Kietakai kiekis: " << kietakai.size() << endl;

    auto end_split = high_resolution_clock::now();
    chrono::duration<double> duration_split = end_split - start_split;
    cout << "Skirstymo i dvi grupes trukme: " << duration_split.count() << " s\n";

    // 2. Rūšiavimas
    auto start_sort = high_resolution_clock::now();

    cout << "Rikiavimo budas: " << rikiavimas << endl; // Debug

    char rikiavimas_local = rikiavimas;

    // Optimizacija: paskaičiuojam visiems galutinius balus prieš sort
    for (auto& s : vargsai) s.skaiciuotiCache();
    for (auto& s : kietakai) s.skaiciuotiCache();

    auto sortFunction = [rikiavimas_local](const Studentas& a, const Studentas& b) {
        if (rikiavimas_local == 'a') {
            return a.galutinisVidurkis() < b.galutinisVidurkis();
        } else if (rikiavimas_local == 'm') {
            return a.galutinisMediana() < b.galutinisMediana();
        }
        return false;
    };

    sort(vargsai.begin(), vargsai.end(), sortFunction);
    sort(kietakai.begin(), kietakai.end(), sortFunction);

    auto end_sort = high_resolution_clock::now();
    chrono::duration<double> duration_sort = end_sort - start_sort;
    cout << "Rusiavimo didejimo tvarka trukme: " << duration_sort.count() << " s\n";

    // 3. Išvedimas į failus
    auto start_output = high_resolution_clock::now();

    char cwd[1024];
    _getcwd(cwd, sizeof(cwd));
    cout << "Failai bus kuriami kataloge: " << cwd << endl;

    ofstream outFileVargsai("vargsai.txt");
    ofstream outFileKietakai("kietakai.txt");

    if (!outFileVargsai || !outFileKietakai) {
        throw runtime_error("Nepavyko atidaryti failu isvedimui.");
    }

    spausdinti(vargsai, outFileVargsai);
    spausdinti(kietakai, outFileKietakai);

    outFileVargsai.close();
    outFileKietakai.close();

    auto end_output = high_resolution_clock::now();
    chrono::duration<double> duration_output = end_output - start_output;
    cout << "Isvedimo i failus trukme: " << duration_output.count() << " s\n";

    cout << "Failai vargsai.txt ir kietakai.txt sekmingai atnaujinti.\n";
}

// Failo įvedimo apdorojimas
void handleFileInput(Vector<Studentas>& studentai) {
    string failoPav;
    bool success = false;
    do {
        cout << "Iveskite failo pavadinima: ";
        cin >> failoPav;
        auto start = high_resolution_clock::now();
        success = skaitymas(studentai, failoPav);
        auto end = high_resolution_clock::now();
        chrono::duration<double> duration = duration_cast<chrono::duration<double>>(end - start);
        cout << "Failo nuskaitymo trukme: " << duration.count() << " s" << endl;
    } while (!success);
    sortAndOutputStudents(studentai);
}

// Studentų duomenų išvedimas į ekraną arba failą
void handleOutput(const Vector<Studentas>& studentai) {
    char outputChoice;
    cout << "Pasirinkite isvedimo buda (s - isvedimas i ekrana, f - isvedimas i faila): ";
    while (!(cin >> outputChoice) || (outputChoice != 's' && outputChoice != 'f')) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }

    if (outputChoice == 's') {
        spausdinti(studentai, cout);
    } else if (outputChoice == 'f') {
        string outputFileName;
        cout << "Iveskite failo pavadinima: ";
        cin >> outputFileName;
        ofstream outFile(outputFileName);
        if (!outFile) {
            throw runtime_error("Nepavyko sukurti failo: " + outputFileName);
        } else {
            spausdinti(studentai, outFile);
            outFile.close();
            cout << "Duomenys sekmingai irasyti i faila: " << outputFileName << endl;
        }
    }
}

// Studentų failų generavimas
void generateStudentFiles() {
    const Vector<int> studentCounts = {1000, 10000, 100000, 1000000, 10000000};
    for (int count : studentCounts) {
        auto start = high_resolution_clock::now();

        string fileName = "studentai" + to_string(count) + ".txt";
        ofstream outFile(fileName);
        if (!outFile) {
            throw runtime_error("Nepavyko sukurti failo: " + fileName);
        }

        outFile << left << setw(15) << "Vardas" << setw(20) << "Pavarde";
        for (int i = 1; i <= 15; ++i) {
            outFile << setw(5) << ("p" + to_string(i));
        }
        outFile << setw(5) << "egz" << "\n";

        for (int i = 1; i <= count; ++i) {
            outFile << left << setw(15) << ("Vardas" + to_string(i)) << setw(20) << ("Pavarde" + to_string(i));
            int ndSkaicius = 15;
            for (int j = 0; j < ndSkaicius; ++j) {
                outFile << setw(5) << (rand() % 10 + 1);
            }
            outFile << setw(5) << (rand() % 10 + 1) << "\n";
        }

        outFile.close();

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<chrono::seconds>(end - start);
        cout << "Failas " << fileName << " sekmingai sukurtas per " << duration.count() << " s.\n";
    }
}