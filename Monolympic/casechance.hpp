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
        std::cout << "Vous êtes sur une case Chance (position " << getPosition() << ")." << std::endl;
        //génère un nombre aléatoire entre 1 et 10
        int nombreAleatoire = rand() % 10 + 1;
        // load file 
        std::string filename = "assets/chance/" + std::to_string(nombreAleatoire) + ".jpg";
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            std::cerr << "Erreur lors du chargement de l'image de la case chance" << std::endl;
        }
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        sprite.setScale(1.0f, 1.0f);
        window.draw(sprite);
        window.display();
        sf::sleep(sf::seconds(5));
        window.clear();
        actionCaseChance(nombreAleatoire, J, window, points);
    }

    void actionCaseChance(int nombreAleatoire, Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const {
        const int nombreCases = 40;
        const int pointsGagnes = 20;
        const int pointsPerdus = 20;

        switch (nombreAleatoire) {
            case 1:
                // Si J.fermetureville == true
                // J.fermetureville = false
                break;
            case 2:
                // Se rendre à Concorde
                J.getPion()->deplacerVers(points[3]);
                // Mettre à jour la position du pion
                if (J.getPion()->getPos() >= 3) {
                    J.setPoints(J.getPoints() + pointsGagnes);
                }
                 J.getPion()->setPosition(points[3]);
                 J.getPion()->setPos(3);
         
                break;
            case 3: // Gagner 10 points
                J.setPoints(J.getPoints() + 10);
                break;
            case 4:
                J.getPion()->deplacerVers(points[24]);
                 
                // Mettre à jour la position du pion
                if (J.getPion()->getPos() >= 24) {
                    J.setPoints(J.getPoints() + pointsGagnes);
                }

                J.getPion()->setPosition(points[24]);
                J.getPion()->setPos(24);

                break;
            case 5:
                // Dispensez d'un quiz
                break;
            case 6:
                // -20 points
                if (J.getPoints() >= pointsPerdus) {
                    J.setPoints(J.getPoints() - pointsPerdus);
                }
                break;
            case 7:
                 // -20 points
                if (J.getPoints() >= pointsPerdus) {
                    J.setPoints(J.getPoints() - pointsPerdus);
                }
                break;
            case 8:
             // -20 points
                if (J.getPoints() >= pointsPerdus) {
                    J.setPoints(J.getPoints() - pointsPerdus);
                }
                break;
            case 9:
               // reculez de 3 cases
                J.getPion()->deplacerVers(points[J.getPion()->getPos() - 3]);
                J.getPion()->setPosition(points[J.getPion()->getPos() - 3]);
                J.getPion()->setPos(J.getPion()->getPos() - 3);

                break;
            case 10:
                // Rendez-vous à la case fermeture de ville
                J.getPion()->deplacerVers(points[30]);
                // Mettre à jour la position du pion
                 J.getPion()->setPosition(points[30]);
                    J.getPion()->setPos(30);
                break;
            default:
                std::cout << "Erreur lors de la génération du nombre aléatoire" << std::endl;
                break;
        }
    }


};
