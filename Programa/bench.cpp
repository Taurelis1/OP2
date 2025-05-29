#include <iostream>
#include <vector>
#include <chrono>
#include "Vector.h"
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main() {
   // unsigned int sizes[] = {10000, 100000, 1000000, 10000000, 100000000};

   // cout << "Elementu skaicius | std::vector (s) | Vector (s)" << endl;
   // cout << "-----------------|-----------------|------------" << endl;

  //  for (unsigned int sz : sizes) {
        // std::vector matavimas
     //   auto start1 = high_resolution_clock::now();
     //   std::vector<int> v1;
      //  for (unsigned int i = 1; i <= sz; ++i) v1.push_back(i);
      //  auto end1 = high_resolution_clock::now();
       // double time1 = duration<double>(end1 - start1).count();

        // Vector matavimas
     //   auto start2 = high_resolution_clock::now();
       // Vector<int> v2;
      //  for (unsigned int i = 1; i <= sz; ++i) v2.push_back(i);
     //   auto end2 = high_resolution_clock::now();
      //  double time2 = duration<double>(end2 - start2).count();

//cout << sz << "           | " << std::fixed << std::setprecision(6) << time1 << "      | " << time2 << endl;
    
    const size_t N = 100000000;
// std::vector test
{
    std::vector<int> v1;
    size_t reallocs1 = 0;
    for (size_t i = 0; i < N; ++i) {
        if (v1.size() == v1.capacity()) ++reallocs1;
        v1.push_back(i);
    }
    std::cout << "std::vector perskirstymų: " << reallocs1 << std::endl;
} // v1 sunaikinamas čia

// Vector test
{
    Vector<int> v2;
    size_t reallocs2 = 0;
    for (size_t i = 0; i < N; ++i) {
        if (v2.size() == v2.capacity()) ++reallocs2;
        v2.push_back(i);
    }
    std::cout << "Vector perskirstymų: " << reallocs2 << std::endl;
} // v2 sunaikinamas čia
    return 0;
}