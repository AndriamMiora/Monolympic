#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Pion.hpp"
#include "Des.hpp"
#include "Button.hpp"
#include "case.hpp"
#include "casechance.hpp"
#include "casedepart.hpp"
#include "casefermeture.hpp"
#include "casenormale.hpp"
#include "casepropriete.hpp"
#include "casequiz.hpp"
#include "caseservicepublic.hpp"
#include "casetaxe.hpp"
#include "joueur.hpp"
#include "casepayante.hpp"
#include <utility>
#pragma once
#include <vector>
#include <list>


class Tableau {
    private:
    std::vector<Case*> cases; // vecteur de cases pour le plateau de jeu 
    std::list<Joueur*> joueurs; // Utilisez une liste pour les joueurs
public:
    Tableau() { // Constructeur par défaut pour initialiser le tableau en ajoutant des cases de chaque type au vecteur de cases 
        ajouterCaseDepart(0, 0); addPropertyCase(1 , 10, false);
        addQuizCase(2); addPropertyCase(3 , 10, false);
        addTaxCase(4 , 10); addNormalCase(5);
        addPropertyCase(6, 7, false); addChanceCase(7);
        addPropertyCase(8 , 7, false); addPropertyCase(9 , 4, false);
        addNormalCase(10); addPropertyCase(11 , 4, false);
        addServiceCase(12, "Électricité"); addPropertyCase(13 , 4, false);
        addPropertyCase(14 , 7, false); addChanceCase(15);
        addPropertyCase(16 , 7, false); addQuizCase(17);
        addPropertyCase(18 , 7, false); addPropertyCase(19 , 13, false);
        addNormalCase(20); addPropertyCase(21 , 13, false);
        addPropertyCase(22 , 13, false); addChanceCase(23);
        addPropertyCase(24 , 13, false); addPropertyCase(25 , 13, false);
        addTaxCase(26 , 10); addPropertyCase(27 , 13, false);
        addQuizCase(28); addPropertyCase(29 , 10, false);
        addCloseCityCase(30); addPropertyCase(31 , 10, false);
        addPropertyCase(32 , 10, false); addQuizCase(33);
        addPropertyCase(34 , 4, false); addServiceCase(35, "Main d'œuvre");
        addChanceCase(36); addPropertyCase(37 , 4, false);
        addServiceCase(38, "Eau"); addPropertyCase(39 , 10, false);
    }

    std::vector<sf::Vector2f> getPoints(); // Méthode pour obtenir le vecteur de points pour le placement des cases (en pixels)

    std::pair<std::vector<sf::Sprite>, int>initializeDiceSprites(Des& des, sf::Vector2f buttonPosition, int& position, std::vector<sf::Vector2f> points, Joueur* joueur, sf::RenderWindow& window);
    // initialise les sprites des dés (selon les valeurs des dés) et renvoie un vecteur de sprites et la somme des dés

    // fonctions d'ajout de cases au vecteur de cases

   void addChanceCase(int position) {
        cases.push_back(new CaseChance(position));
    }

    void ajouterCaseDepart(int position, int medailles) {
        cases.push_back(new CaseDepart(medailles, position));
    }

    void addCloseCityCase(int position) {
        cases.push_back(new CaseFermetureVille(position));
    }

    void addNormalCase(int position) {
        cases.push_back(new CaseNormale(position));
    }

    void addPropertyCase(int position, int cout, bool etat) {
        cases.push_back(new CasePropriete(position, cout, etat));
    }

    void addQuizCase(int position) {
        cases.push_back(new CaseQuiz(position));
    }

    void addServiceCase(int position, const std::string& type) {
        cases.push_back(new CaseServicePublic(position, 10, false, type));
    }

    void  addTaxCase(int position, int montant) {
        cases.push_back(new CaseTaxe(montant,position));
    }

   // Renvoie la case à une position donnée
    Case* getCaseAtPosition(int pos) const {
        for (Case* c : cases) {
            if (c->getPosition() == pos) {
                return c;
            }
        }
        return nullptr; // Aucune case à cette position
    }

    // Méthode pour effectuer l'action de la case à une position donnée
    void actionAtPosition(int& pos, sf ::RenderWindow& window, std::vector<sf::Vector2f> points, Joueur* joueur) {
        Case* c = getCaseAtPosition(pos);
        if (c != nullptr) {
            // afficher pion jour 
            joueur->getPion()->afficher(window);
            c->action( *joueur , window, points);
            pos = joueur->getPion()->getPos();
            std::cout << "nombre de médailles : " << joueur->getPoints() << std::endl;
        } else {
            std::cout << "Aucune case à la position " << pos << "." << std::endl;
        }
    }
    // Méthode pour ajouter un joueur au tableau
    void addJoueur(Joueur* joueur) {
        joueurs.push_back(joueur);
    }

    // Méthode pour récupérer tous les joueurs
    std::list<Joueur*> getJoueurs() const {
        return joueurs;
    }

    // Méthode pour récupérer un joueur par son index dans le vecteur
    Joueur* getJoueurAtIndex(int index) const {
        int i = 0;
        for (Joueur* j : joueurs) {
            if (i == index) {
                return j;
            }
            ++i;
        }
        return nullptr;
    }

    // Méthode pour mettre à jour le pion et les points d'un joueur
    void updateJoueur(Joueur* joueur, Pion* pion, int points) {
        joueur->setPion(pion);
        joueur->setPoints(points);
    }

// fonctions pour récuper les positions des cases

sf::Vector2f placement(std::vector<sf::Vector2f>& positions, sf::Vector2f& positionDepartGauche, sf::Vector2f& positionDepartDroite, sf::Vector2i& caseNormaleSize, sf::Vector2i& caseNormaleRotateSize, sf::Vector2i& caseDepartSize, float& offsetY, float& offsetYTop, float& basImage, float& hautImage, sf::Texture& texture, sf::Sprite& sprite, sf::RenderWindow& window) {
    positions.push_back(positionDepartDroite);

    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartDroite.x - caseNormaleSize.x * (i + 1), positionDepartDroite.y);
        positions.push_back(position);
    }

    positions.push_back(positionDepartGauche);

    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartGauche.x - caseNormaleRotateSize.x, positionDepartGauche.y - caseNormaleRotateSize.y * (i + 1));
        positions.push_back(position);
    }

    sf::Vector2f positionDepartGaucheTop(positionDepartGauche.x, hautImage + offsetYTop);
    positions.push_back(positionDepartGaucheTop);

    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartGaucheTop.x + caseDepartSize.x + (caseNormaleSize.x * i), positionDepartGaucheTop.y);
        positions.push_back(position);
    }

    sf::Vector2f positionDepartDroiteTop(positions.back().x + caseNormaleSize.x, positionDepartGaucheTop.y);
    positions.push_back(positionDepartDroiteTop);

    for (int i = 8; i >= 0; --i) {
        sf::Vector2f position(positionDepartDroite.x + caseNormaleRotateSize.x, positionDepartDroite.y - caseNormaleRotateSize.y * (i + 1));
        positions.push_back(position);
    }

    return positionDepartDroiteTop ; 
}


std::tuple<std::vector<sf::Vector2f>, sf::Vector2i, sf::Vector2i, sf::Vector2i, sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f> initializePositions() {
    sf::Texture texture;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Plateau de jeu");
    sf::Sprite sprite; 
    texture.loadFromFile("board.png"); 
    sprite.setTexture(texture);

    sf::Vector2i caseNormaleSize(49, 84);
    sf::Vector2i caseNormaleRotateSize(84, 49);
    sf::Vector2i caseDepartSize(85, 84);

    float offsetY = -138.0f;
    float offsetYTop = 57.0f;

    float basImage = static_cast<float>(texture.getSize().y);
    float hautImage = 0.0f;

    std::vector<sf::Vector2f> positions;

    sf::Vector2f positionDepartGauche(310.0f, basImage + offsetY);
    sf::Vector2f positionDepartDroite(positionDepartGauche.x + 10.6 * caseNormaleSize.x, positionDepartGauche.y);
    sf::Vector2f positionDepartGaucheTop(positionDepartGauche.x, hautImage + offsetYTop);

    sf::Vector2f positionDepartDroiteTop = placement(positions, positionDepartGauche, positionDepartDroite, 
    caseNormaleSize, caseNormaleRotateSize, caseDepartSize, offsetY, offsetYTop, basImage, 
    hautImage, texture, sprite, window);

    return std::make_tuple(positions, caseNormaleSize, caseNormaleRotateSize, caseDepartSize, 
    positionDepartDroite, positionDepartGauche, positionDepartGaucheTop,positionDepartDroiteTop);
}


};