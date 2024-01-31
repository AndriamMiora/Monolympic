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

    void initializeSprite(sf::Sprite& sprite, const sf::Vector2f& position, const sf::Vector2f& origin, const sf::Vector2f& scale) const  { 
    // fonction pour initialiser les sprites
    sprite.setOrigin(origin.x, origin.y);
    sprite.setPosition(position);
    sprite.setScale(scale.x, scale.y);
}


    void drawsprite(sf::RenderWindow& window, sf::Sprite& spriteA, sf::Sprite& spriteB, sf::Sprite& spriteC, sf::Sprite& spriteD, sf::Sprite& sprite) const {
        // Dessiner les sprites
        window.draw(sprite);
        window.draw(spriteA);
        window.draw(spriteB);
        window.draw(spriteC);
        window.draw(spriteD);
        // Afficher la fenêtre
        window.display();
    }

    void action(Joueur& J, sf::RenderWindow& window,std::vector<sf::Vector2f> points) const override{
        //std::cout << "Vous êtes sur une case Quiz (position " << getPosition() << ")." << std::endl;
        //génère un nombre aléatoire entre 1 et 10
        int nombreAleatoire = rand() % 10 + 1;
        // load file 
        if (J.getCarteDispenseQuiz()) { // si le joueur a une carte chance dispense quiz il l'utiliser afin de ne pas faire le quiz
            sf :: Texture texture;
            if (!texture.loadFromFile("assets/dispensequiz.jpg")) {
                std::cerr << "Erreur lors du chargement de l'image de la case quiz" << std::endl;
            }
            sf::Sprite sprite; sprite.setTexture(texture);
            sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
            sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
            sprite.setScale(1.0f, 1.0f);

            window.draw(sprite);
            window.display();
            sf::sleep(sf::seconds(5));
            window.clear();
            J.setCarteDispenseQuiz(false);
            return;
        }
        actionCaseQuiz(nombreAleatoire, J, window, points); // réaliser le quiz correspondant au nombre aléatoire généré = carte quiz qui a été tirée
    }

// Fonction pour gérer la réponse
void handleResponse(sf::RenderWindow& window, const sf::Sprite& sprite, Joueur& J, std :: string bonneReponse, std::string reponse) const {
    window.draw(sprite);
    window.display();
    if (reponse == bonneReponse) {
        animateBonneReponse(window, J);
        J.setPoints(J.getPoints() + 20);
    } else {
        animateMauvaiseReponse(window, J);
        J.setPoints(std::max(0, J.getPoints() - 20));
    }
    sf::sleep(sf::milliseconds(500));  
}

    // Fonction pour gérer le clic de la souris sur les réponses
bool handleMouseClick(sf::RenderWindow& window, float mouseX, float mouseY, const sf::Sprite& spriteA,
    const sf::Sprite& spriteB, const sf::Sprite& spriteC, const sf::Sprite& spriteD,Joueur& J, std::string bonneReponse) const {
    if (spriteA.getGlobalBounds().contains(mouseX, mouseY)) {
        handleResponse(window, spriteA, J, bonneReponse, "A");
        return true;
    } else if (spriteB.getGlobalBounds().contains(mouseX, mouseY)) {
        handleResponse(window, spriteB, J, bonneReponse, "B");
        return true;
    } else if (spriteC.getGlobalBounds().contains(mouseX, mouseY)) {
        handleResponse(window, spriteC, J, bonneReponse, "C");
        return true;
    } else if (spriteD.getGlobalBounds().contains(mouseX, mouseY)) {
        handleResponse(window, spriteD, J, bonneReponse, "D");
        return true;
    }
    return false;
}


// Fonction pour simuler la réponse du bot
void simulateBotAnswer(sf::RenderWindow& window, const sf::Sprite& sprite, const sf::Sprite& spriteA,
                       const sf::Sprite& spriteB, const sf::Sprite& spriteC, const sf::Sprite& spriteD,
                       Joueur& J, std :: string bonneReponse) const {
    window.draw(sprite);
    window.display();
    sf::sleep(sf::milliseconds(1000));  // Ajustez le délai si nécessaire
    int nombreAleatoire = rand() % 4 + 1;
    std :: string reponse ;
    if (nombreAleatoire == 1) {
        reponse = "A";
        window.draw(spriteA);
    } else if (nombreAleatoire == 2) {
        reponse = "B";
        window.draw(spriteB);
    } else if (nombreAleatoire == 3) {
        reponse = "C";
        window.draw(spriteC);
    } else if (nombreAleatoire == 4) {
        reponse = "D";
        window.draw(spriteD);
    }
    if (reponse == bonneReponse) {
        J.setPoints(J.getPoints() + 20);
    } else {
        J.setPoints(std::max(0, J.getPoints() - 20));
    }
    sf::sleep(sf::milliseconds(500));  // Ajustez le délai si nécessaire
}

std::string reponse(int nombreAleatoire) const {  // fonction qui retourne la bonne réponse en fonction de la carte quiz tirée
    switch (nombreAleatoire) {
        case 1:
            return "B";
        case 2:
            return "B";
        case 3:
            return "C";
        case 4:
            return "A";
        case 5:
            return "B";
        case 6:
            return "B";
        case 7:
            return "A";
        case 8:
            return "A";
        case 9:
            return "C";
        case 10:
            return "B";
    }
    return "A";
    }


void initializeSprites(sf::RenderWindow& window, sf::Sprite& spriteA, sf::Sprite& spriteB, sf::Sprite& spriteC,
                       sf::Sprite& spriteD, sf::Sprite& sprite, sf::Texture& textureA, sf::Texture& textureB,
                       sf::Texture& textureC, sf::Texture& textureD, sf::Texture& texture) const {
    initializeSprite(spriteA, sf::Vector2f(640, 360), sf::Vector2f(textureA.getSize().x / 2.0f, textureA.getSize().y / 2.0f),
                     sf::Vector2f(0.07f, 0.07f));
    initializeSprite(spriteB, sf::Vector2f(640, 385), sf::Vector2f(textureB.getSize().x / 2.0f, textureB.getSize().y / 2.0f),
                     sf::Vector2f(0.07f, 0.07f));
    initializeSprite(spriteC, sf::Vector2f(640, 410), sf::Vector2f(textureC.getSize().x / 2.0f, textureC.getSize().y / 2.0f),
                     sf::Vector2f(0.07f, 0.07f));
    initializeSprite(spriteD, sf::Vector2f(640, 440), sf::Vector2f(textureD.getSize().x / 2.0f, textureD.getSize().y / 2.0f),
                     sf::Vector2f(0.07f, 0.07f));
    initializeSprite(sprite, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f),
                     sf::Vector2f(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f), sf::Vector2f(1.0f, 1.0f));
}


    void actionCaseQuiz(int nombreAleatoire, Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const { // fonction qui réalise le quiz
        sf::Texture textureA, textureB, textureC, textureD, texture;
        textureA.loadFromFile("assets/Quiz/A.png"); textureB.loadFromFile("assets/Quiz/B.png");
        textureC.loadFromFile("assets/Quiz/C.png"); textureD.loadFromFile("assets/Quiz/D.png");
        texture.loadFromFile("assets/Quiz/" + std::to_string(nombreAleatoire) + ".jpg");
        sf::Sprite spriteA, spriteB, spriteC, spriteD, sprite;
        spriteA.setTexture(textureA); spriteB.setTexture(textureB); spriteC.setTexture(textureC); spriteD.setTexture(textureD); sprite.setTexture(texture);
        initializeSprites(window, spriteA, spriteB, spriteC, spriteD, sprite, textureA, textureB, textureC, textureD, texture);
        // Dessiner les sprites 
        drawsprite(window, spriteA, spriteB, spriteC, spriteD, sprite);
        std :: string bonneReponse = reponse(nombreAleatoire);
        bool reponse = false;
        if (J.getBot()) {
            reponse = true;
            simulateBotAnswer(window, sprite, spriteA, spriteB, spriteC, spriteD, J, bonneReponse); return;
        }
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close(); return;
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    reponse = handleMouseClick(window, event.mouseButton.x, event.mouseButton.y,spriteA, spriteB, spriteC, spriteD, J, bonneReponse);
                }
            }
            if (reponse) {
                return;
            }
        }
    }


    
// Fonction qui anime la bonne réponse
void animateBonneReponse(sf::RenderWindow& window, Joueur& J) const {
    // Charger les textures "bonneReponse.jpg" et "continuer1.png"
    sf::Texture bonneReponseTexture;
    bonneReponseTexture.loadFromFile("assets/bonneReponse.jpg");
    sf::Texture continuerTexture;
    continuerTexture.loadFromFile("assets/continuer1.png");
    // Charger la texture du fond
    sf::Texture fondTexture;
    fondTexture.loadFromFile("assets/background.png");
    // Créer les sprites pour le fond, l'image "bonneReponse.jpg" et le bouton "continuer"
    sf::Sprite fondSprite(fondTexture); sf::Sprite bonneReponseSprite(bonneReponseTexture);
    sf::Sprite continuerSprite(continuerTexture);
    // Initialiser les positions et échelles des sprites
    initializeSprite(bonneReponseSprite, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f),sf::Vector2f(bonneReponseTexture.getSize().x / 2.0f, bonneReponseTexture.getSize().y / 2.0f),sf::Vector2f(1.0f, 1.0f));
    initializeSprite(continuerSprite, sf::Vector2f(640, 550),sf::Vector2f(continuerSprite.getLocalBounds().width / 2.0f, continuerSprite.getLocalBounds().height / 2.0f),sf::Vector2f(0.2f, 0.2f));
    // Boucle d'affichage
    while (window.isOpen()) {
        // Gérer les événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); return;  // Sortir de la fonction
            }
            if (!J.getBot() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (continuerSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    sf::sleep(sf::milliseconds(100));  return;  // Sortir de la fonction
                } } }
        // Affichage des sprites
        window.clear();window.draw(fondSprite); window.draw(bonneReponseSprite); window.draw(continuerSprite);
        window.display();}
}

// Fonction qui anime la mauvaise réponse
void animateMauvaiseReponse(sf::RenderWindow& window, Joueur& J) const {
    // Charger les textures "mauvaiseReponse.jpg" et "continuer1.png"
    sf::Texture mauvaiseReponseTexture;
    mauvaiseReponseTexture.loadFromFile("assets/mauvaiseReponse.jpg");
    sf::Texture continuerTexture;
    continuerTexture.loadFromFile("assets/continuer2.png");
    // Charger la texture du fond
    sf::Texture fondTexture;
    fondTexture.loadFromFile("assets/background.png");
    // Créer les sprites pour le fond, l'image "mauvaiseReponse.jpg" et le bouton "continuer"
    sf::Sprite fondSprite(fondTexture); sf::Sprite mauvaiseReponseSprite(mauvaiseReponseTexture);
    sf::Sprite continuerSprite(continuerTexture);
    // Initialiser les positions et échelles des sprites
    initializeSprite(mauvaiseReponseSprite, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f),sf::Vector2f(mauvaiseReponseTexture.getSize().x / 2.0f, mauvaiseReponseTexture.getSize().y / 2.0f),sf::Vector2f(1.0f, 1.0f));
    initializeSprite(continuerSprite, sf::Vector2f(640, 550),sf::Vector2f(continuerSprite.getLocalBounds().width / 2.0f, continuerSprite.getLocalBounds().height / 2.0f),sf::Vector2f(0.2f, 0.2f));
    // Boucle d'affichage
    while (window.isOpen()) {
        // Gérer les événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); return;  // Sortir de la fonction
            }
            if (!J.getBot() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (continuerSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    sf::sleep(sf::milliseconds(1000));  return;  // Sortir de la fonction
                } } }
        // Affichage des sprites
        window.clear();window.draw(fondSprite); window.draw(mauvaiseReponseSprite); window.draw(continuerSprite);
        window.display();}
}
};
