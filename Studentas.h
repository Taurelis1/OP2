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

using namespace std;
using namespace std::chrono;

struct Studentas {
    string var;
    string pav;
    vector<int> nd;
    int egz;
};

extern char rikiavimas; // Declare as extern

double Mediana(const vector<int>& vec);
void clearInput();
string generuotiVarda();
string generuotiPavarde();
bool skaitymas(vector<Studentas>& studentai, const string& failoPav);
void spausdinti(const vector<Studentas>& studentai, std::ostream& out);
void rikiuotiStudentus(vector<Studentas>& studentai, char rikiavimas);
void ivestiStudentus(vector<Studentas>& studentai);
void handleFileInput(vector<Studentas>& studentai);
void handleSorting(vector<Studentas>& studentai);
void handleOutput(const vector<Studentas>& studentai);
void generateStudentFiles();
void sortAndOutputStudents(vector<Studentas>& studentai);
void skaidyti3_vector(vector<Studentas>& studentai);

#endif // STUDENTAS_H