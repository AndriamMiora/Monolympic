#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#include <string.h>
#pragma once
#include <vector>
#include "joueur.hpp"

// Classe dérivée pour les cases fermeture ville
class CaseFermetureVille : public Case {
public:
    CaseFermetureVille(int _position) : Case(_position) {}

    std :: string findtexture(Joueur& J) const {
         if (J.getCarteOuvertureVille() == true) { // si le joueur a une carte chance ouverture ville il l'utiliser afin que la ville ne soit pas fermée
            J.setFermerVille(false); 
            J.setCarteOuvertureVille(false);
            return "assets/fermeture3.jpg";
        }
        else {
            if (J.getPoints() >= 20) { // si le joueur a assez de points pour payer l'amende de fermeture de ville
                J.setPoints(J.getPoints() - 20);
                J.setFermerVille(false);
                return "assets/fermeture1.jpg";
            }
            else {
                // sinon bloquer le joueur pour 2 tours
                J.setFermerVille(true);
                return "assets/fermeture2.jpg";
                J.setPoints(0);
            }
        }
        
    }
    
    void gererjoueur(Joueur& J, sf::RenderWindow& window, sf :: Sprite& sprite,  sf :: Sprite& continuerSprite, sf :: Sprite& fondSprite) const {
         // Boucle d'affichage
            while (window.isOpen()) {
            sf::Event event; // Gérer les événements
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                window.close();
                return; } // Sortir de la fonction
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (continuerSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            // Afficher les sprites
                            window.draw(continuerSprite);
                            // Afficher la fenêtre
                            window.display();
                            // Attendre un court instant pour éviter le clic immédiat sur "continuer" dans la nouvelle fenêtre
                            sf::sleep(sf::milliseconds(1000));  // Vous pouvez ajuster le délai si nécessaire
                            return;  // Sortir de la fonction
                }
            }
        // Effacer le contenu de la fenêtre
        window.clear();
        // Afficher les sprites
        window.draw(fondSprite);
        window.draw(sprite);
        window.draw(continuerSprite);
        // Afficher la fenêtre
        window.display();
            }
        }
        }

// meme fonction que findtexture mais pour les bots
void actionbot(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points, int number, int number2) const override {
        if (J.getCarteOuvertureVille() == true) {
            J.setFermerVille(false);
            J.setCarteOuvertureVille(false);
        }
        else {
            if (J.getPoints() >= 20) {
                J.setPoints(J.getPoints() - 20);
                J.setFermerVille(false);
            }
            else {
                // bloquer le joueur pour 2 tours
                J.setFermerVille(true);
                J.setPoints(0);
            }
        }
        }

        // action de la case fermeture ville
    void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const override{
        // Gérer le clic sur le bouton "continuer" si on est un bot
        if (J.getBot() == true) {
            actionbot(J, window, points, 0, 0);
            }
        else {
        sf :: Texture texture; texture.loadFromFile(findtexture(J));
        sf::Sprite sprite; sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        sprite.setScale(1.0f, 1.0f);
         // Charger la texture du fond
        sf::Texture fondTexture; fondTexture.loadFromFile("assets/background.png");
        // Créer le sprite pour le fond
        sf::Sprite fondSprite; fondSprite.setTexture(fondTexture);
        fondSprite.setScale(1.0f, 1.0f);
        // Charger la texture de l'image "continuer.png"
        sf::Texture continuerTexture;
        continuerTexture.loadFromFile("assets/continuer2.png");
        sf::Sprite continuerSprite;
        continuerSprite.setTexture(continuerTexture);
        continuerSprite.setOrigin(continuerSprite.getLocalBounds().width / 2.0f, continuerSprite.getLocalBounds().height / 2.0f);
        continuerSprite.setPosition(650, 585);  // Position spécifiée pour "continuerSprite"
        continuerSprite.setScale(0.2f, 0.2f);
        // Afficher les sprites
        window.draw(fondSprite);
        window.draw(sprite);
        window.draw(continuerSprite);
        window.display();
        gererjoueur(J, window, sprite, continuerSprite, fondSprite);}
    }
};
