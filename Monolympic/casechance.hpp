#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#pragma once
#include <vector>
#include <string>
#include "joueur.hpp"

// Classe dérivée pour les cases chance
class CaseChance : public Case {
public:
    CaseChance(int _position) : Case(_position) {}

    void action(Joueur& J, sf::RenderWindow& window,std::vector<sf::Vector2f> points) const override{
        //std::cout << "Vous êtes sur une case Chance (position " << getPosition() << ")." << std::endl;
        //génère un nombre aléatoire entre 1 et 10 pour choisir la carte chance
        int nombreAleatoire = rand() % 10 + 1;
        // affiche la carte chance correspondante
        std::string filename = "assets/chance/" + std::to_string(nombreAleatoire) + ".jpg";
        sf::Texture texture;
        texture.loadFromFile(filename);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        sprite.setScale(1.0f, 1.0f);
        window.draw(sprite);
        window.display();
        sf::sleep(sf::seconds(1));
        // effectue l'action correspondante
        actionCaseChance(nombreAleatoire, J, window, points);
    }

    // Méthode pour effectuer l'action selon le nombre aléatoire généré = carte chance qui a été tirée
    void actionCaseChance(int nombreAleatoire, Joueur& J, sf::RenderWindow& window, const std::vector<sf::Vector2f>& points) const {
    switch (nombreAleatoire) {
        case 1:  J.setCarteOuvertureVille(true); break;
        case 2: { J.getPion()->deplacerVers(points[3]);
            if (J.getPion()->getPos() >= 3) {
                J.setPoints(J.getPoints() + 20);
            }
            J.getPion()->setPosition(points[3]); J.getPion()->setPos(3); break;
        }
        case 3: J.setPoints(J.getPoints() + 10); break;
        case 4: { J.getPion()->deplacerVers(points[24]);
        if (J.getPion()->getPos() >= 24) {
                J.setPoints(J.getPoints() + 20);
            }
            J.getPion()->setPosition(points[24]); J.getPion()->setPos(24);break;
        }
        case 5: J.setCarteDispenseQuiz(true); break;
        case 6:
        case 7:
        case 8:
            if (J.getPoints() >= 20) {
                J.setPoints(J.getPoints() - 20);
            }
            break;
        case 9: { J.getPion()->deplacerVers(points[J.getPion()->getPos() - 3]);
            J.getPion()->setPosition(points[J.getPion()->getPos() - 3]);
            J.getPion()->setPos(J.getPion()->getPos() - 3); break;
        }
        case 10: { J.getPion()->deplacerVers(points[30]);
            J.getPion()->setPosition(points[30]);
            J.getPion()->setPos(30); break;
    }} }
};
