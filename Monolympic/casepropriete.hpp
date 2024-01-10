
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#include "joueur.hpp"
#pragma once
#include <vector>
// Classe dérivée pour les cases propriété
class CasePropriete : public Case {
public:
    CasePropriete(int _position, int _cout, bool _estAchete) : Case(_position), cout(_cout), estAchete(_estAchete) {}

    // Méthode pour effectuer l'action de la case à une position donnée
   // Méthode pour effectuer l'action de la case à une position donnée
void action(Joueur& J, sf::RenderWindow& window) const override {
    if (J.getPoints() >= cout && !estAchete) {
        // Affichage d'un message au milieu avec fond
        sf::Font font;
        if (!font.loadFromFile("police1.otf")) {
            std::cerr << "Erreur lors du chargement de la police" << std::endl;
        }

        sf::Text message;
        message.setFont(font);
        message.setString("Vous allez vous deplacer sur une case propriete. Voulez-vous l'acheter pour " + std::to_string(cout) + " medailles ?");
        message.setCharacterSize(24);
        message.setFillColor(sf::Color::White);

        // Centrer le texte sur la fenêtre
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
        message.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

        // Fond
        sf::RectangleShape fond(sf::Vector2f(textRect.width + 20, textRect.height + 20));
        fond.setFillColor(sf::Color(0, 0, 0, 150));
        fond.setOrigin(fond.getSize().x / 2.0f, fond.getSize().y / 2.0f);
        fond.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

        // croix rouge pour non
        sf::RectangleShape croix1(sf::Vector2f(20, 20));
        croix1.setFillColor(sf::Color::Red);
        croix1.setOrigin(croix1.getSize().x / 2.0f, croix1.getSize().y / 2.0f);
        croix1.setPosition(window.getSize().x / 2.0f + textRect.width / 2.0f + 10, window.getSize().y / 2.0f - textRect.height / 2.0f - 10);

        // cercle vert pour oui
        sf::CircleShape cercle1(10);
        cercle1.setFillColor(sf::Color::Green);
        cercle1.setOrigin(cercle1.getRadius(), cercle1.getRadius());
        cercle1.setPosition(window.getSize().x / 2.0f - textRect.width / 2.0f - 10, window.getSize().y / 2.0f - textRect.height / 2.0f - 10);

        // Affichage
        window.draw(fond);
        window.draw(message);
        window.draw(croix1);
        window.draw(cercle1);
        window.display(); 

        // Boucle pour attendre la réponse du joueur
       // Boucle pour attendre la réponse du joueur
bool reponse = false;
while (!reponse) {
    sf::Event event;
    while (window.pollEvent(event)) {
        // Si on appuie sur la croix rouge
        if (event.type == sf::Event::Closed) {
            window.close();
            return;  // Sortir de la fonction
        }
        // Si on clique sur le cercle vert
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (cercle1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    reponse = true;
                    J.setPoints(J.getPoints() - cout);

                    // Affichage au milieu de la carte de la propriété png
                    sf::Texture texture;
                    if (!texture.loadFromFile("test.png")) {
                        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
                    }
                    sf::Sprite sprite;
                    sprite.setTexture(texture);
                    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
                    sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
                    window.draw(sprite);
                    window.display();
                    sf::sleep(sf::seconds(2));
                }
            }
        }
        // Si on clique sur la croix rouge
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (croix1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    reponse = false;
                    return;  // Sortir de la fonction
                }
            }
        }
    }
}

    }
}

private:
    int cout;
    bool estAchete;
};