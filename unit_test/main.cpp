#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_USE_GMTIME_R
#include "catch_amalgmated.hpp"
#include "Studentas.h"

TEST_CASE("Studentas Rule of Five") {
    std::vector<int> nd = {10, 9, 8, 7, 6};
    Studentas s1("Jonas", "Jonaitis", nd, 9);

    SECTION("Copy constructor") {
        Studentas s2 = s1;
        REQUIRE(s2.vardas() == "Jonas");
        REQUIRE(s2.pavarde() == "Jonaitis");
        REQUIRE(s2.namuDarbai() == nd);
        REQUIRE(s2.egzaminas() == 9);
    }

    SECTION("Move constructor") {
        Studentas s2 = std::move(s1);
        REQUIRE(s2.vardas() == "Jonas");
    }

    SECTION("Copy assignment") {
        Studentas s3;
        s3 = Studentas("Jonas", "Jonaitis", nd, 9);
        REQUIRE(s3.pavarde() == "Jonaitis");
    }

    SECTION("Move assignment") {
        Studentas s4;
        s4 = Studentas("Jonas", "Jonaitis", nd, 9);
        REQUIRE(s4.egzaminas() == 9);
    }
}

TEST_CASE("Studentas IO operators") {
    std::vector<int> nd = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6};
    Studentas s1("Jonas", "Jonaitis", nd, 9);

    std::stringstream ss;
    ss << s1;
    Studentas s2;
    ss >> s2;

    REQUIRE(s2.vardas() == "Jonas");
    REQUIRE(s2.pavarde() == "Jonaitis");
    REQUIRE(s2.namuDarbai() == nd);
    REQUIRE(s2.egzaminas() == 9);
}