#include "Studentas.h"
#include <iostream>
#include <sstream>
#include <cassert>
using namespace std;

int main() {
    vector<int> nd = {10, 9, 8, 7, 6};
    Studentas s1("Jonas", "Jonaitis", nd, 9);

    // Copy constructor
    Studentas s2 = s1;
    assert(s2.vardas() == "Jonas");
    assert(s2.pavarde() == "Jonaitis");

    // Move constructor
    Studentas s3 = std::move(s2);
    assert(s3.vardas() == "Jonas");

    // Copy assignment
    Studentas s4;
    s4 = s1;
    assert(s4.pavarde() == "Jonaitis");

    // Move assignment
    Studentas s5;
    s5 = std::move(s4);
    assert(s5.egzaminas() == 9);

    // Įvesties/išvesties operatoriai
    std::stringstream ss;
    ss << s1;
    Studentas s6;
    ss >> s6; // Paprastas testas, ar galima nuskaityti

    cout << "Visi Studentas Rule of Five ir IO operatoriai veikia teisingai!" << endl;
    return 0;
}