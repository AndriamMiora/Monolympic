// Let Catch provide main():
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "case.hpp"
#include "casedepart.hpp"
#include "casequiz.hpp"
#include "casechance.hpp"
#include "casefermeture.hpp"
#include "casenormale.hpp"
#include "casepropriete.hpp"
#include "caseservicepublic.hpp"
#include "casetaxe.hpp"
#include "casepayante.hpp"
#include "joueur.hpp"
#include "Pion.hpp"
#include "Pion.cpp"
#include "Des.hpp"
#include "Des.cpp"
#include "tableau.hpp"
#include "tableau.cpp"
#include "Button.hpp"


// include your classes here

TEST_SUITE("Create Case") {
  TEST_CASE("1: Create Case départ") {
    // une case prend une position en paramètre et un nombre de médailles
    int p = 0;
    CaseDepart c(20, p);
    CHECK(c.getNbMedailles() == 20);
    CHECK(c.getPosition() == 0);
  }
  TEST_CASE("2: Create Case propriété") {
    // une case prend une position en paramètre et un nombre de médailles
    CasePropriete c(20, 10, false);
    CHECK(c.getPosition () == 20);
    CHECK(c.getCout() == 10);
    CHECK(c.getEtat() == false);
    CHECK(c.getNombreMaxInstallations() == 10);
    CHECK(c.getNombrePiscines() == 0);
    CHECK(c.getNombreSalles() == 0);
    CHECK(c.getNombreStades() == 0);
   
  }
  TEST_CASE("3: Create Case Taxe") {
    // une case prend une position en paramètre et un nombre de médailles
    CaseTaxe T(20, 10);
    CHECK(T.getPosition () == 10);
    CHECK(T.getMontant() == 20);
  
  }
  TEST_CASE("4: Create Case Service Public") {
    // une case prend une position en paramètre et un nombre de médailles
    CaseServicePublic S(6, 30, false, "Electricité");
    CHECK(S.getCout () == 30);
    CHECK(S.getNomService() == "Electricité");  
    CHECK(S.getPosition() == 6);
    CHECK(S.getEtat() == false);
  }
  TEST_CASE("5: Create Case Quiz") {
    // une case prend une position en paramètre et un nombre de médailles
    CaseQuiz Q(6);
    CHECK(Q.getPosition() == 6);
  }

  TEST_CASE("6: Create Case Chance") {
    // une case prend une position en paramètre et un nombre de médailles
    CaseChance C(8);
    CHECK(C.getPosition() == 8);
  }


}
TEST_SUITE("Create element de jeu") {

  TEST_CASE("1: Create Pion et joueur") {
    // une case prend une position en paramètre et un nombre de médailles
    Pion* pion = new Pion();
    std::vector<int> casesAchetees;
    Joueur j(pion, 20, casesAchetees, false);
    CHECK(j.getPoints() == 20);
    CHECK(j.getPion()->getPosition() == sf::Vector2f(0,0));
    CHECK(j.getPion()->getPos() == 0);
    CHECK(j.getPion()->getCheminImage() == "images/pion.png");
    CHECK(j.getCarteOuvertureVille() == false);
    CHECK(j.getCarteDispenseQuiz() == false);
    CHECK(j.getFermerVille() == false);
    CHECK(j.getBot() == false);
  }
  TEST_CASE("2: Create Button") {
  }

  }

TEST_SUITE("Create Tableau") {

  Tableau* t = new Tableau();
  TEST_CASE("1: Ajout de joueur") {
    Pion* pion = new Pion();
    Pion* pion2 = new Pion();
    std::vector<int> casesAchetees;
    std::vector<int> casesAchetees2 = {1,2,3};
    Joueur j(pion2, 20, casesAchetees, false);
    Joueur j2(pion, 30, casesAchetees2, false);
    t->addJoueur(&j2);
    t->addJoueur(&j);
    CHECK(t->getJoueurs().size() == 2);
    CHECK(t->getJoueurAtIndex(0)->getPoints() == 30);
    CHECK(t->getJoueurAtIndex(1)->getPoints() == 20);
    CHECK((j==j2) == false);
    CHECK((j<j2) == true);
    CHECK((j>j2) == false);

}

TEST_CASE("2 : Verifications des cases") {
 Tableau t;
 // verifie si le type de la case à la position 0 est bien une case départ
 // implementer fonction gettype

}
}
