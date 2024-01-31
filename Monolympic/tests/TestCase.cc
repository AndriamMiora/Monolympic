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



TEST_SUITE("Create Case") { // on teste la création des cases de notre jeu
  TEST_CASE("1: Creation Case départ") {
    int p = 0;
    CaseDepart c(20, p);
    CHECK(c.getNbMedailles() == 20);
    CHECK(c.getPosition() == 0);
  }
  TEST_CASE("2: Creation Case propriété") {
    CasePropriete c(20, 10, false);
    CHECK(c.getPosition () == 20);
    CHECK(c.getCout() == 10);
    CHECK(c.getEtat() == false);
    CHECK(c.getNombrePiscines() == 0);
    CHECK(c.getNombreSalles() == 0);
    CHECK(c.getNombreStades() == 0);
   
  }
  TEST_CASE("3: Creation Case Taxe") {
    CaseTaxe T(20, 10);
    CHECK(T.getPosition () == 10);
    CHECK(T.getMontant() == 20);
  
  }
  TEST_CASE("4: Creation Case Service Public") {
    CaseServicePublic S(6, 30, false, "Electricité");
    CHECK(S.getCout () == 30);
    CHECK(S.getNomService() == "Electricité");  
    CHECK(S.getPosition() == 6);
    CHECK(S.getEtat() == false);
  }
  TEST_CASE("5: Creation Case Quiz") {
    CaseQuiz Q(6);
    CHECK(Q.getPosition() == 6);
  }

  TEST_CASE("6: Creation Case Chance") {
    CaseChance C(8);
    CHECK(C.getPosition() == 8);
  }


}
TEST_SUITE("Creattion element de jeu") {

  TEST_CASE("1: Creation Pion et joueur") {
    Pion* pion = new Pion(); // on crée un pion , on initialise un joueur avec 20 points et un pion en position 0 (case départ) et on ne le met pas en bot
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
  }

TEST_SUITE("Tableau") {

  Tableau* t = new Tableau();
  TEST_CASE("1: Ajout de joueur") {
    // on crée deux joueurs et on les ajoute au tableau t
    Pion* pion = new Pion();
    Pion* pion2 = new Pion();
    std::vector<int> casesAchetees;
    std::vector<int> casesAchetees2 = {1,2,3};
    Joueur j(pion2, 20, casesAchetees, false);
    Joueur j2(pion, 30, casesAchetees2, false);
    t->addJoueur(&j2); // on ajoute le joueur j2 au tableau 
    t->addJoueur(&j); // on ajoute le joueur j au tableau
    CHECK(t->getJoueurs().size() == 2);  // on vérifie que le tableau contient bien 2 joueurs
    CHECK(t->getJoueurAtIndex(0)->getPoints() == 30); // on vérifie que le joueur j2 est bien en position 0
    CHECK(t->getJoueurAtIndex(1)->getPoints() == 20); // on vérifie que le joueur j est bien en position 1
    CHECK((j==j2) == false); // test des opérateurs de comparaison de joueurs qui verifient que les joueurs ont le même nombre de points
    CHECK((j<j2) == true);
    CHECK((j>j2) == false);
  }
    TEST_CASE("2 : Déplacement de pions"){

    Pion* pion = new Pion();
    Pion* pion2 = new Pion();
    Tableau* t = new Tableau();
    std::vector<sf :: Vector2f> points = t->getPoints();
    // deplacement de pion
    pion->deplacerVers(points[1]);
    pion->setPos(1);
    CHECK(pion->getPos() == 1);
    // deplacement de pion2
    pion2->deplacerVers(points[20]);
    pion2->setPos(20);
    CHECK(pion2->getPos() == 20);

    }
}



TEST_SUITE ("Utilisation des cases"){ 
 Tableau t;
  TEST_CASE("1 : fonctions d'achats de cases payantes"){
    Pion* pion = new Pion();
    Pion* pion2 = new Pion();
    std::vector<int> casesAchetees;
    std::vector<int> casesAchetees2;
    Joueur j(pion, 20, casesAchetees, true); // on initialise un joueur avec 20 points et un pion en position 0 (case départ) et on le met en bot
    Joueur j2(pion2, 30, casesAchetees2, true); // on initialise un joueur avec 30 points et un pion en position 0 (case départ) et on le met en bot
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    t.addJoueur(&j); // on ajoute le joueur au tableau

    CasePropriete c(20, 10, false); // on initialise une case propriété avec un cout de 10 Médailles et qui n'est pas achetée
    c.action(j, window, t.getPoints()); // on fait l'action de la case sur le joueur j
    // si le bot a acheté la case
    if (j.getCasesAchetees().size() == 1) {
      CHECK(j.getPoints() == 10);
      CHECK(c.getEtat() == true);
      CHECK(j.getCasesAchetees().size() == 1);
      CHECK(j.getCasesAchetees()[0] == 20);
    }
    // si le bot n'a pas acheté la case
    else {
      CHECK(j.getPoints() == 20);
      CHECK(c.getEtat() == false);
      CHECK(j.getCasesAchetees().size() == 0);
    }

    CaseServicePublic S(6, 30, false, "Electricité"); // on initialise une case service public avec un cout de 30 Médailles et un nom "Electricité" et qui n'est pas achetée
    S.action(j2, window, t.getPoints()); // on fait l'action de la case sur le joueur j2
    // si le bot a acheté la case
    if (j2.getCasesAchetees().size() == 1) {
      CHECK(j2.getPoints() == 20);
      CHECK(S.getEtat() == true);
      CHECK(j2.getCasesAchetees().size() == 1);
      CHECK(j2.getCasesAchetees()[0] == 6);
    }
    // si le bot n'a pas acheté la case
    else {
      CHECK(j2.getPoints() == 30);
      CHECK(S.getEtat() == false);
      CHECK(j2.getCasesAchetees().size() == 0);
    }

  }

  TEST_CASE("2 : fonctions de fermeture de ville"){
    Pion* pion = new Pion();
    Pion* pion2 = new Pion();

    CaseFermetureVille F(20); // on initialise une case fermeture ville en position 20
    std::vector<int> casesAchetees;
    std::vector<int> casesAchetees2;

    Joueur j3(pion, 10, casesAchetees, true); //le joueur j3 a 10 points et un pion en position 0 (case départ) et on le met en bot
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    F.action(j3, window, t.getPoints()); // on fait l'action de la case sur le joueur j3 qui n'a pas assez de points pour payer la fermeture de ville
    CHECK(j3.getFermerVille() == true);
    CHECK(j3.getPoints() == 0);

    Joueur j4(pion2, 40, casesAchetees2, true); //le joueur j4 a 40 points et un pion en position 0 (case départ) et on le met en bot
    F.action(j4, window, t.getPoints()); // on fait l'action de la case sur le joueur j4 qui a assez de points pour payer la fermeture de ville
    CHECK(j4.getFermerVille() == false);
    CHECK(j4.getPoints() == 20); 
    
  }
  TEST_CASE("3 : fonctions de taxe"){
    Pion* pion = new Pion();
    std::vector<int> casesAchetees;
    Joueur j5(pion, 20, casesAchetees, true); //le joueur j5 a 20 points et un pion en position 0 (case départ) et on le met en bot
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    t.addJoueur(&j5);
    CaseTaxe T(20, 10); // on initialise une case taxe avec un cout de 20 Médailles et en position 10
    T.action(j5, window, t.getPoints()); // on fait l'action de la case sur le joueur j5
    CHECK(j5.getPoints() == 0); 
  } 
  TEST_CASE("4 : fonctions d'achats d'installations"){}

}

