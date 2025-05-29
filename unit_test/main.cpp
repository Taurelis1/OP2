#define CATCH_CONFIG_MAIN
#include "catch_amalgmated.hpp"
#include "Vector.h"

TEST_CASE("Vector push_back and operator[]", "[Vector]") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
}

TEST_CASE("Vector copy constructor and assignment", "[Vector]") {
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2(v1);
    REQUIRE(v2.size() == 3);
    REQUIRE(v2[1] == 2);

    Vector<int> v3;
    v3 = v1;
    REQUIRE(v3.size() == 3);
    REQUIRE(v3[2] == 3);
}

TEST_CASE("Vector move constructor and assignment", "[Vector]") {
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2(std::move(v1));
    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 1);

    Vector<int> v3;
    v3 = std::move(v2);
    REQUIRE(v3.size() == 3);
    REQUIRE(v3[1] == 2);
}

TEST_CASE("Vector insert and erase", "[Vector]") {
    Vector<int> v = {1, 2, 4};
    v.insert(v.begin() + 2, 3);
    REQUIRE(v[2] == 3);
    REQUIRE(v.size() == 4);

    v.erase(v.begin() + 1);
    REQUIRE(v[1] == 3);
    REQUIRE(v.size() == 3);
}

TEST_CASE("Vector assign and clear", "[Vector]") {
    Vector<int> v;
    v.assign(5, 7);
    REQUIRE(v.size() == 5);
    for (int i = 0; i < 5; ++i)
        REQUIRE(v[i] == 7);

    v.clear();
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty());
}

TEST_CASE("Vector comparison operators", "[Vector]") {
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {1, 2, 3};
    Vector<int> v3 = {1, 2, 4};
    REQUIRE(v1 == v2);
    REQUIRE(v1 != v3);
    REQUIRE(v1 < v3);
    REQUIRE(v3 > v2);
}