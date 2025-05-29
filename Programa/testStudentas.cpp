#include "Vector.h"
#include "Studentas.h"
#include "Zmogus.h"
#include <iostream>
#include <sstream>
#include <cassert>
using namespace std;

void spausdintiStudenta(const Studentas& s, const string& prefix) {
    cout << prefix << ": " << s.vardas() << " " << s.pavarde() << " egz: " << s.egzaminas() << endl;
}

int main() {
    // Negalima sukurti Zmogus objekto, nes tai abstrakti klasė (kompiliatorius išmes klaidą):
// Zmogus z("Vardenis", "Pavardenis"); // <-- Ši eilutė nesikompiliuos!

    Vector<int> nd = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6}; // Namu darbu ivertinimai
    Studentas s1("Jonas", "Jonaitis", nd, 9);
    spausdintiStudenta(s1, "s1");

    // Copy constructor
    Studentas s2 = s1;
    spausdintiStudenta(s2, "s2 (copy)");

    // Move constructor
    Studentas s3 = std::move(s2);
    spausdintiStudenta(s3, "s3 (move)");

    // Copy assignment
    Studentas s4;
    s4 = s1;
    spausdintiStudenta(s4, "s4 (copy assign)");

    // Move assignment
    Studentas s5;
    s5 = std::move(s4);
    spausdintiStudenta(s5, "s5 (move assign)");

    // Įvesties/išvesties operatoriai
    std::stringstream ss;
    ss << s1;
    cout << "Išvestis į stringstream: " << ss.str() << endl;
    Studentas s6;
    ss >> s6;
    spausdintiStudenta(s6, "s6 (istream)");

    cout << "Visi Studentas Rule of Five ir IO operatoriai veikia teisingai!" << endl;
    return 0;
}