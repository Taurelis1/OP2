#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include "Vector.h"
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <limits>
#include "Zmogus.h"

class Studentas : public Zmogus {
private:
    Vector<int> nd_;
    int egz_;
    mutable double cachedVidurkis = -1;
    mutable double cachedMediana = -1;

public:
    // Konstruktoriai ir destruktorius
    Studentas();
    Studentas(const std::string& var, const std::string& pav, const Vector<int>& nd, int egz);
    ~Studentas();

    // Rule of Five
    Studentas(const Studentas& other);
    Studentas(Studentas&& other) noexcept;
    Studentas& operator=(const Studentas& other);
    Studentas& operator=(Studentas&& other) noexcept;

    // Get'eriai (override)
    std::string vardas() const override { return var_; }
    std::string pavarde() const override { return pav_; }
    Vector<int> namuDarbai() const { return nd_; }
    int egzaminas() const { return egz_; }

    // Set'eriai 
    void setEgzaminas(int egz) { egz_ = egz; }

    // Galutinio balo skaičiavimas
    double galutinisVidurkis() const;
    double galutinisMediana() const;
    void skaiciuotiCache() const;

    // Įvesties/išvesties operatoriai
    friend std::istream& operator>>(std::istream& in, Studentas& s);
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s);

   
    void info() const override {
        std::cout << "Studentas: " << var_ << " " << pav_ << std::endl;
    }
};

// Pagalbinės funkcijos
double Mediana(const Vector<int>& vec);
void clearInput();
std::string generuotiVarda();
std::string generuotiPavarde();
bool skaitymas(Vector<Studentas>& studentai, const std::string& failoPav);
void spausdinti(const Vector<Studentas>& studentai, std::ostream& out);
void rikiuotiStudentus(Vector<Studentas>& studentai, char rikiavimas);
void ivestiStudentus(Vector<Studentas>& studentai);
void sortAndOutputStudents(Vector<Studentas>& studentai);
void handleFileInput(Vector<Studentas>& studentai);
void handleOutput(const Vector<Studentas>& studentai);
void generateStudentFiles();

#endif // STUDENTAS_H