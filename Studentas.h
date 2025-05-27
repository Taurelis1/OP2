#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <limits>

class Studentas {
private:
    std::string var_;
    std::string pav_;
    std::vector<int> nd_;
    int egz_;
    mutable double cachedVidurkis = -1;
    mutable double cachedMediana = -1;

public:
    // Konstruktoriai
    Studentas() : var_(""), pav_(""), egz_(0) {}
    Studentas(const std::string& var, const std::string& pav, const std::vector<int>& nd, int egz)
        : var_(var), pav_(pav), nd_(nd), egz_(egz) {}
    ~Studentas();

    // Get'eriai
    std::string vardas() const { return var_; }
    std::string pavarde() const { return pav_; }
    std::vector<int> namuDarbai() const { return nd_; }
    int egzaminas() const { return egz_; }

    // Set'eriai 
    void setEgzaminas(int egz) { egz_ = egz; }

    // Galutinio balo skaičiavimas
    double galutinisVidurkis() const;
    double galutinisMediana() const;
    void skaiciuotiCache() const;

    // Draugiškos funkcijos
    friend std::istream& operator>>(std::istream& in, Studentas& s);
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s);
};

// Pagalbinės funkcijos
double Mediana(const std::vector<int>& vec);
void clearInput();
std::string generuotiVarda();
std::string generuotiPavarde();
bool skaitymas(std::vector<Studentas>& studentai, const std::string& failoPav);
void spausdinti(const std::vector<Studentas>& studentai, std::ostream& out);
void rikiuotiStudentus(std::vector<Studentas>& studentai, char rikiavimas);
void ivestiStudentus(std::vector<Studentas>& studentai);
void sortAndOutputStudents(std::vector<Studentas>& studentai);
void handleFileInput(std::vector<Studentas>& studentai);
void handleOutput(const std::vector<Studentas>& studentai);
void generateStudentFiles();

#endif // STUDENTAS_H