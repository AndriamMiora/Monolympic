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

    void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const override{
        sf :: Texture texture;

        if (J.getCarteOuvertureVille() == true) {
            J.setFermerVille(false);
            J.setCarteOuvertureVille(false);

            if (!texture.loadFromFile("assets/fermeture3.jpg")) {
                std::cerr << "Erreur lors du chargement de l'image de la case quiz" << std::endl;
            }
        }
        else {
            if (J.getPoints() >= 20) {
                J.setPoints(J.getPoints() - 20);
                J.setFermerVille(true);
                if (!texture.loadFromFile("assets/fermeture1.jpg")) {
                std::cerr << "Erreur lors du chargement de l'image de la case quiz" << std::endl;
            }
            }
            else {
                // bloquer le joueur pour 2 tours
                J.setFermerVille(true);
                if (!texture.loadFromFile("assets/fermeture2.jpg")) {
                std::cerr << "Erreur lors du chargement de l'image de la case quiz" << std::endl;
            }
            }
        }
        sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
            sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
            sprite.setScale(1.0f, 1.0f);


         // Charger la texture du fond
    sf::Texture fondTexture;
    fondTexture.loadFromFile("assets/background.png");

    // Créer le sprite pour le fond
    sf::Sprite fondSprite;
    fondSprite.setTexture(fondTexture);
    fondSprite.setScale(1.0f, 1.0f);

        // Charger la texture de l'image "continuer.png"
        sf::Texture continuerTexture;
        if (!continuerTexture.loadFromFile("assets/continuer2.png")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image continuer" << std::endl;
         }

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

        // Gérer le clic sur le bouton "continuer" si on est un bot
        if (J.getBot() == true) {
            sf::sleep(sf::milliseconds(1000));  // Vous pouvez ajuster le délai si nécessaire               
            }
        else {
             // Boucle d'affichage
            while (window.isOpen()) {
            // Gérer les événements
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                window.close();
                return;  // Sortir de la fonction
                }
                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        if (continuerSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            // Gérer le clic sur le bouton "continuer"
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
    }
};