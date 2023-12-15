// Let Catch provide main():
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "case.hpp"
#include "casedepart.hpp"

// include your classes here

TEST_SUITE("Case") {
  TEST_CASE("1: Create Case départ") {
    // une case prend une position en paramètre et un nombre de médailles
    Point p = {0, 0}; 
    CaseDepart c(10, p);
    CHECK(c.getNbMedailles() == 10);
    CHECK(c.getCoordonnees().x == 0);
    CHECK(c.getCoordonnees().y == 0);

  }

}

