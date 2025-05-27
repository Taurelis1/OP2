#include "Studentas.h"
#include "Mylib.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

const int MAX_STUDENTU_SKAICIUS = 10000000; // Nustatome maksimalu studentu skaiciu

void promptForSortingMethod() {
    cout << "Pasirinkite rusiavimo buda (a - galutinis vidurkis, m - galutinis mediana): ";
    while (!(cin >> rikiavimas) || (rikiavimas != 'a' && rikiavimas != 'm')) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }
}

int main() {
    try {
        auto start = high_resolution_clock::now(); // Pradeti laikmati

        std::srand(std::time(0)); 

        vector<Studentas> studentai;
        char pasirinkimas;

        cout << "Pasirinkite veiksma (s - generuoti studentu failus, g - generuoti viska, i - ivesti duomenis, f - skaityti is failo, q - uzdaryti programa): ";
        while (!(cin >> pasirinkimas) || (pasirinkimas != 's' && pasirinkimas != 'g' && pasirinkimas != 'i' && pasirinkimas != 'f' && pasirinkimas != 'q')) {
            clearInput();
            cout << "Neteisinga ivestis. Bandykite dar karta: ";
        }

        if (pasirinkimas == 'q') {
            return 0;
        } else if (pasirinkimas == 's') {
            generateStudentFiles();
        } else if (pasirinkimas == 'g') {
            int studentuSkaicius;
            cout << "Iveskite studentu skaiciu (maksimalus skaicius: " << MAX_STUDENTU_SKAICIUS << "): ";
            while (!(cin >> studentuSkaicius) || studentuSkaicius <= 0 || studentuSkaicius > MAX_STUDENTU_SKAICIUS) {
                clearInput();
                cout << "Neteisinga ivestis. Bandykite dar karta: ";
            }
            try {
                studentai.reserve(studentuSkaicius); // Rezervuojame atminties vieta
                for (int i = 0; i < studentuSkaicius; i++) {
                    Studentas student;
                    student.var = generuotiVarda();
                    student.pav = generuotiPavarde();
                    int ndSkaicius = 15; // Fixed number of marks
                    student.nd.resize(ndSkaicius);
                    for (int j = 0; j < ndSkaicius; j++) {
                        student.nd[j] = std::rand() % 10 + 1; // Generuojame balus nuo 1 iki 10
                    }
                    student.egz = std::rand() % 10 + 1; // Generuojame egzamino bala nuo 1 iki 10
                    studentai.push_back(student);
                }
                sortAndOutputStudents(studentai);
            } catch (const std::bad_alloc& e) {
                cout << "Nepavyko sukurti studentu: " << e.what() << endl;
                return 1;
            }
        } else if (pasirinkimas == 'i') {
            ivestiStudentus(studentai);
            sortAndOutputStudents(studentai);
        } else if (pasirinkimas == 'f') {
            promptForSortingMethod();
            handleFileInput(studentai);
        }

        auto end = high_resolution_clock::now(); // Baigti laikmati
        auto duration = duration_cast<std::chrono::seconds>(end - start);
        cout << "Programos vykdymo trukme: " << duration.count() << " s" << endl;

    } catch (const std::exception& e) {
        cout << "Ivyko klaida: " << e.what() << endl;
    }

    return 0;
}