#include <iostream>
#include <vector>
#include <chrono>
#include "Vector.h"
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main() {
    unsigned int sizes[] = {10000, 100000, 1000000, 10000000, 100000000};

    cout << "Elementu skaicius | std::vector (s) | Vector (s)" << endl;
    cout << "-----------------|-----------------|------------" << endl;

    for (unsigned int sz : sizes) {
        // std::vector matavimas
        auto start1 = high_resolution_clock::now();
        std::vector<int> v1;
        for (unsigned int i = 1; i <= sz; ++i) v1.push_back(i);
        auto end1 = high_resolution_clock::now();
        double time1 = duration<double>(end1 - start1).count();

        // Vector matavimas
        auto start2 = high_resolution_clock::now();
        Vector<int> v2;
        for (unsigned int i = 1; i <= sz; ++i) v2.push_back(i);
        auto end2 = high_resolution_clock::now();
        double time2 = duration<double>(end2 - start2).count();

cout << sz << "           | " << std::fixed << std::setprecision(6) << time1 << "      | " << time2 << endl;
    }
    return 0;
}