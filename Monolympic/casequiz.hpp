#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#pragma once
#include <vector>
#include <string>
#include "joueur.hpp"
// Classe dérivée pour les cases quiz
class CaseQuiz : public Case {
public:
    CaseQuiz(int _position) : Case(_position) {}

     void action(Joueur& J, sf::RenderWindow& window,std::vector<sf::Vector2f> points) const override{
        std::cout << "Vous êtes sur une case Quiz (position " << getPosition() << ")." << std::endl;
        //génère un nombre aléatoire entre 1 et 10
        int nombreAleatoire = rand() % 10 + 1;
        // load file 

        if (J.getCarteDispenseQuiz()) {
            sf :: Texture texture;
            if (!texture.loadFromFile("assets/dispensequiz.jpg")) {
                std::cerr << "Erreur lors du chargement de l'image de la case quiz" << std::endl;
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
            return;
        }
        actionCaseQuiz(nombreAleatoire, J, window, points);
    }

    void actionCaseQuiz(int nombreAleatoire, Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const {
    
    sf::Texture textureA, textureB, textureC, textureD, texture;
    if (!textureA.loadFromFile("assets/Quiz/A.png")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image A" << std::endl;
    }

    if (!textureB.loadFromFile("assets/Quiz/B.png")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image B" << std::endl;
    }

    if (!textureC.loadFromFile("assets/Quiz/C.png")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image C" << std::endl;
    }

    if (!textureD.loadFromFile("assets/Quiz/D.png")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image D" << std::endl;
    }

    if (!texture.loadFromFile("assets/Quiz/" + std::to_string(nombreAleatoire) + ".jpg")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image A" << std::endl;
    }

    sf::Sprite spriteA, spriteB, spriteC, spriteD, sprite;
    spriteA.setTexture(textureA);
    spriteA.setOrigin(textureA.getSize().x / 2.0f, textureA.getSize().y / 2.0f);
    spriteA.setPosition(640, 360);
    spriteA.setScale(0.07f, 0.07f);

    spriteB.setTexture(textureB);
    spriteB.setOrigin(textureB.getSize().x / 2.0f, textureB.getSize().y / 2.0f);
    spriteB.setPosition(640, 385);
    spriteB.setScale(0.07f, 0.07f);

    spriteC.setTexture(textureC);
    spriteC.setOrigin(textureC.getSize().x / 2.0f, textureC.getSize().y / 2.0f);
    spriteC.setPosition(640, 410);
    spriteC.setScale(0.07f, 0.07f);

    spriteD.setTexture(textureD);
    spriteD.setOrigin(textureD.getSize().x / 2.0f, textureD.getSize().y / 2.0f);
    spriteD.setPosition(640, 440);
    spriteD.setScale(0.07f, 0.07f);

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    sprite.setScale(1.0f, 1.0f);

     // Dessiner les sprites
        window.draw(sprite);
        window.draw(spriteA);
        window.draw(spriteB);
        window.draw(spriteC);
        window.draw(spriteD);
        // Afficher la fenêtre
        window.display();
    
    // Sélection de la bonne réponse en fonction du nombre aléatoire
    char bonneReponse;
    switch (nombreAleatoire) {
        case 1:
            bonneReponse = 'A';
            break;
        case 2:
            bonneReponse = 'B';
            break;
        case 3:
            bonneReponse = 'C';
            break;
        case 4:
            bonneReponse = 'D';
            break;
        case 5:
            bonneReponse = 'A';
            break;
        case 6:
            bonneReponse = 'B';
            break;
        case 7:
            bonneReponse = 'C';
            break;
        case 8:
            bonneReponse = 'D';
            break;
        case 9:
            bonneReponse = 'A';
            break;
        case 10:
            bonneReponse = 'B';
            break;
        default:
            // Gérer le cas où nombreAleatoire n'est pas dans la plage attendue
            std::cerr << "Erreur : nombre aléatoire hors de la plage attendue." << std::endl;
            return;
    }

    // Boucle d'attente d'une réponse
    bool reponse = false;
     // Boucle d'affichage
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Gérer les événements (cliquer sur la croix rouge pour fermer la fenêtre)
            if (event.type == sf::Event::Closed) {
                window.close();
                return;  // Sortir de la fonction
            }

            // Gérer les clics de souris
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (spriteA.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        // Gérer la réponse A
                        reponse = true;
                        if (bonneReponse == 'A') {
                            animateBonneReponse(window);
                            J.setPoints(J.getPoints() + 20);
                        } else {
                            animateMauvaiseReponse(window);
                            if (J.getPoints() - 20 < 0) {
                                J.setPoints(0);
                            } else {
                                J.setPoints(J.getPoints() - 20);
                            }
                        }
                    } else if (spriteB.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        // Gérer la réponse B
                        reponse = true;
                        if (bonneReponse == 'B') {
                            animateBonneReponse(window);
                            J.setPoints(J.getPoints() + 20);
                        } else {
                            animateMauvaiseReponse(window);
                             if (J.getPoints() - 20 < 0) {
                                J.setPoints(0);
                            } else {
                                J.setPoints(J.getPoints() - 20);
                            }
                        }
                    } else if (spriteC.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        // Gérer la réponse C
                        reponse = true;
                        if (bonneReponse == 'C') {
                            animateBonneReponse(window);
                            J.setPoints(J.getPoints() + 20);
                        } else {
                            animateMauvaiseReponse(window);
                             if (J.getPoints() - 20 < 0) {
                                J.setPoints(0);
                            } else {
                                J.setPoints(J.getPoints() - 20);
                            }
                        }
                    } else if (spriteD.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        // Gérer la réponse D
                        reponse = true;
                        if (bonneReponse == 'D') {
                            animateBonneReponse(window);

                            J.setPoints(J.getPoints() + 20);
                        } else {
                            animateMauvaiseReponse(window);
                             if (J.getPoints() - 20 < 0) {
                                J.setPoints(0);
                            } else {
                                J.setPoints(J.getPoints() - 20);
                            }
                        }
                    }
                }
            }
        }

        

       

        // Si la réponse est donnée, sortir de la boucle
        if (reponse) {
            break;
        }
    }
}
    
// Fonction qui anime la bonne réponse
void animateBonneReponse(sf::RenderWindow& window) const {
    // Charger la texture de l'image "bonneReponse.png"
    sf::Texture bonneReponseTexture;
    if (!bonneReponseTexture.loadFromFile("assets/bonneReponse.jpg")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image bonneReponse" << std::endl;
        return;
    }

    // Charger la texture de l'image "continuer.png"
    sf::Texture continuerTexture;
    if (!continuerTexture.loadFromFile("assets/continuer1.png")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image continuer" << std::endl;
        return;
    }

    // Créer le sprite pour l'image "bonneReponse.png"
    sf::Sprite bonneReponseSprite;
    bonneReponseSprite.setTexture(bonneReponseTexture);
    bonneReponseSprite.setPosition(450, 160);  // Position spécifiée pour "bonneReponseSprite"
    bonneReponseSprite.setScale(0.62, 0.62);

    // Créer le sprite pour l'image "continuer.png"
    sf::Sprite continuerSprite;
    continuerSprite.setTexture(continuerTexture);
    continuerSprite.setOrigin(continuerSprite.getLocalBounds().width / 2.0f, continuerSprite.getLocalBounds().height / 2.0f);
    continuerSprite.setPosition(610, 478);  // Position spécifiée pour "continuerSprite"
    continuerSprite.setScale(0.1f, 0.1f);

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
                    window.draw(bonneReponseSprite);
                    window.draw(continuerSprite);
                    // Afficher la fenêtre
                    window.display();
                    // Attendre un court instant pour éviter le clic immédiat sur "continuer" dans la nouvelle fenêtre
                    sf::sleep(sf::milliseconds(1000));  // Vous pouvez ajuster le délai si nécessaire
                    return;  // Sortir de la fonction
                }
            }
        }

        // Effacer le contenu de la fenêtre
        window.clear();

        // Afficher les sprites
        window.draw(bonneReponseSprite);
        window.draw(continuerSprite);

        // Afficher la fenêtre
        window.display();
    }
}



// fonction qui anime la mauvaise réponse

void animateMauvaiseReponse(sf::RenderWindow& window) const {
    // Charger la texture de l'image "bonneReponse.png"
    sf::Texture mauvaiseReponseTexture;
    if (!mauvaiseReponseTexture.loadFromFile("assets/mauvaiseReponse.jpg")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image bonneReponse" << std::endl;
    }


    // Charger la texture de l'image "continuer.png"
    sf::Texture continuerTexture;
    if (!continuerTexture.loadFromFile("assets/continuer2.png")) {
        std::cerr << "Erreur lors du chargement de la texture pour l'image continuer" << std::endl;
    }

    // Créer le sprite pour l'image "mauvaiseReponse.png"
    sf::Sprite mauvaiseReponseSprite;
    mauvaiseReponseSprite.setTexture(mauvaiseReponseTexture);
    mauvaiseReponseSprite.setPosition(450, 160);  
    mauvaiseReponseSprite.setScale(0.62, 0.62);


    sf::Sprite continuerSprite;
    continuerSprite.setTexture(continuerTexture);
    continuerSprite.setOrigin(continuerSprite.getLocalBounds().width / 2.0f, continuerSprite.getLocalBounds().height / 2.0f);
    continuerSprite.setPosition(610, 453);  // Position spécifiée pour "continuerSprite"
    continuerSprite.setScale(0.1f, 0.1f);

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
                    window.draw(mauvaiseReponseSprite);
                    window.draw(continuerSprite);
                    // Afficher la fenêtre
                    window.display();
                    // Attendre un court instant pour éviter le clic immédiat sur "continuer" dans la nouvelle fenêtre
                    sf::sleep(sf::milliseconds(1000));  // Vous pouvez ajuster le délai si nécessaire
                    return;  // Sortir de la fonction
                }
            }
        }

        // Effacer le contenu de la fenêtre
        window.clear();

        // Afficher les sprites
        window.draw(mauvaiseReponseSprite);
        window.draw(continuerSprite);

        // Afficher la fenêtre
        window.display();
    }
}
};
