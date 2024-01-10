#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <vector>
#include "case.hpp"
#include "Pion.hpp"
#include "Des.hpp"
#include "Button.hpp"
#include "tableau.hpp"
#include <string>
#include "joueur.hpp"


using namespace std;

int main(){
    // Pour créer une fenêtre de jeu
    sf::RenderWindow window(sf::VideoMode(1280, 720),
    "by Andrianarivo Ashley & Andriambolo-nivo Miora",
    sf::Style::Close | sf::Style::Titlebar); // Style de la fenêtre : Close = bouton fermer, Titlebar = barre de titre

    // Pour charger une police de caractère
    sf::Font stdFont;
    stdFont.loadFromFile("police1.otf");

    // Pour charger une image d'icône de jeu 
    sf::Image favicon;
    favicon.loadFromFile("assets/favicon.png");
    window.setIcon(314, 229, favicon.getPixelsPtr()); // 314x229 est la taille de l'image favicon.png

    // Pour charger une image de fond
    sf::RectangleShape introScreen(sf::Vector2f(1280.0f, 720.0f));
    sf::Texture introScreenTexture;
    introScreenTexture.loadFromFile("large.png");
    introScreen.setTexture(&introScreenTexture);

    // Pour afficher du texte
    sf::Text introScreenText;
    introScreenText.setFont(stdFont);
    introScreenText.setCharacterSize(50);
    introScreenText.setPosition(sf::Vector2f(50.0f, 600.0f));
    // Position du texte en bas à gauche de la fenêtre
    //introScreenText.setFillColor(sf::Color::White);
    //introScreenText.setString("MONOLYMPIC GAMES");


    sf::Text introScreenText2;
    introScreenText2.setFont(stdFont);
    introScreenText2.setCharacterSize(20);
    introScreenText2.setPosition(sf::Vector2f(10.0f, 10.0f));
    introScreenText2.setFillColor(sf::Color::Black);
    introScreenText2.setString("by Andrianarivo Ashley & Andriambolo-nivo Miora\n");

    // créer un bouton pour commencer le jeu
    sf::Texture newGameButtonTexture;
    newGameButtonTexture.loadFromFile("assets/Start2.png");
    sf::RectangleShape newGameButton(sf::Vector2f(316.0f, 94.0f));
    newGameButton.setTexture(&newGameButtonTexture);
    newGameButton.setPosition(sf::Vector2f(480.0f, 210.0f));

    bool gameStarted = false;

    while (!gameStarted) {
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
            if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (newGameButton.getGlobalBounds().contains(mousePos)) {
                    gameStarted = true;
                }
            }
        }

        window.clear();
        window.draw(introScreen);
        window.draw(introScreenText2);
        window.draw(introScreenText);
        window.draw(newGameButton);
        window.display();
    }

    // Pour charger une image de fond pour la sélection des noms des joueurs et des pions
    sf::Texture selectionScreenTexture;
    selectionScreenTexture.loadFromFile("assets/background.png");
    sf::RectangleShape selectionScreen(sf::Vector2f(1280.0f, 720.0f));
    selectionScreen.setTexture(&selectionScreenTexture);

    // créer un bouton pour entrer le nom du joueur
    sf::Texture enternametexture;
    enternametexture.loadFromFile("assets/name.png");
    sf::RectangleShape enternamebutton(sf::Vector2f(500.0f, 500.0f));
    enternamebutton.setTexture(&enternametexture);
    // Calcul de la position pour centrer l'image
    float x = (window.getSize().x - enternamebutton.getSize().x) / 2.0f;
    float y = (window.getSize().y - enternamebutton.getSize().y) / 2.0f;
    enternamebutton.setPosition(sf::Vector2f(x, y));
 
    // box pour entrer le nom du joueur
    sf::RectangleShape nameInputBox(sf::Vector2f(300.0f, 50.0f));
    nameInputBox.setFillColor(sf::Color::Black);
    nameInputBox.setPosition(sf::Vector2f(490.0f, 425.0f));
    // Récupérer la taille de la boîte de texte

    sf::Text nameInputText;
    nameInputText.setFont(stdFont);
    nameInputText.setCharacterSize(20);
    nameInputText.setFillColor(sf::Color::White); // Définir la couleur du texte en blanc

    // Largeur de la fenêtre
    float windowWidth = 1200.0f;

    // Positionner le texte au centre horizontalement en ajustant pour le point d'origine
    float textWidth = nameInputText.getGlobalBounds().width;
    float centerX = (windowWidth - textWidth) / 2.0f;
    float textHeight = nameInputText.getGlobalBounds().height;
    float centerY = 440.0f - textHeight / 2.0f;

    nameInputText.setPosition(sf::Vector2f(centerX, centerY));




    // Ajout bouton pour valider le nom du joueur
    sf::Texture validatetexture;
    validatetexture.loadFromFile("assets/valider.png");
    sf::RectangleShape validatebutton(sf::Vector2f(316.0f, 94.0f));
    validatebutton.setTexture(&validatetexture);
    validatebutton.setPosition(sf::Vector2f(480.0f, 500.0f));
    

    if (gameStarted) {
        bool nameEntered = false;
        string playerName = "";
        while (!nameEntered) {
            sf::Event evt;
            while (window.pollEvent(evt)) {
                if (evt.type == sf::Event::Closed) {
                    window.close();
                }
                if (evt.type == sf::Event::TextEntered) {
                    if (evt.text.unicode >= 32 && evt.text.unicode <= 126) {
                        playerName += static_cast<char>(evt.text.unicode);
                        nameInputText.setString(playerName);
                    }
                    else if (evt.text.unicode == 8 && playerName.length() > 0) {
                        playerName.pop_back();
                        nameInputText.setString(playerName);
                    }
                }
                if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (validatebutton.getGlobalBounds().contains(mousePos)) {
                        nameEntered = true;
                    }
                }
            }

            window.clear();
            window.draw(selectionScreen);
            window.draw(enternamebutton);
            window.draw(nameInputBox);
            window.draw(nameInputText);
            window.draw(validatebutton);
            window.display();
            
        }
    }

    // Créer un bouton pour entrer le nom du joueur avec une image
    sf::Texture chooseImageTexture;
    chooseImageTexture.loadFromFile("assets/chooseimage.png");
    sf::Sprite chooseImageSprite(chooseImageTexture);

    // Calcul de la position pour centrer l'image
    float imageX = (window.getSize().x - chooseImageSprite.getGlobalBounds().width) / 2.0f;
    float imageY = (window.getSize().y - chooseImageSprite.getGlobalBounds().height) / 2.0f;
    chooseImageSprite.setPosition(sf::Vector2f(imageX, imageY));


    // Choix du pions : 4 choix de pions

    sf::Texture pion1texture;
    pion1texture.loadFromFile("assets/pion.png");
    sf::RectangleShape pion1(sf::Vector2f(50.0f, 50.0f));
    pion1.setTexture(&pion1texture);
    pion1.setPosition(sf::Vector2f(550.0f, 440.0f));

    sf::Texture pion2texture;
    pion2texture.loadFromFile("assets/pion2.png");
    sf::RectangleShape pion2(sf::Vector2f(50.0f, 50.0f));
    pion2.setTexture(&pion2texture);
    pion2.setPosition(sf::Vector2f(550.0f + 60.0f, 440.0f));  // Ajout de 60.0f pour décaler le deuxième pion

    sf::Texture pion3texture;
    pion3texture.loadFromFile("assets/pion3.png");
    sf::RectangleShape pion3(sf::Vector2f(50.0f, 50.0f));
    pion3.setTexture(&pion3texture);
    pion3.setPosition(sf::Vector2f(550.0f + 2 * 60.0f, 440.0f));  // Ajout de 2 * 60.0f pour décaler le troisième pion


   

string playerPion = "";
// Code pour la première boucle (sélection du pion)
if (gameStarted) {
    bool pionSelected = false;
    
    while (!pionSelected && window.isOpen()) {
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
            if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (pion1.getGlobalBounds().contains(mousePos)) {
                    pionSelected = true;
                    playerPion = "pion1";
                }
                if (pion2.getGlobalBounds().contains(mousePos)) {
                    pionSelected = true;
                    playerPion = "pion2";
                }
                if (pion3.getGlobalBounds().contains(mousePos)) {
                    pionSelected = true;
                    playerPion = "pion3";
                }
                
            }
        }

        window.clear();
        window.draw(selectionScreen);
        window.draw(chooseImageSprite);
        window.draw(pion1);
        window.draw(pion2);
        window.draw(pion3);

        window.display();
    }
}

if (gameStarted) {
    Tableau tableau;
    std::vector<sf::Vector2f> points = tableau.getPoints();
    Des des;
    int position = 0;

    // Création des joueurs
    Joueur* joueur2 = new Joueur(/* ... */);
    Joueur* joueur1 = new Joueur(/* ... */);
    
    // Initialisation du pion du joueur en bas à droite du plateau
    Pion pion("assets/pion.png",  sf::Vector2f(871.900024, 624.000000) );
    if (playerPion == "pion1") {
        pion.setCheminImage("assets/pion.png");
        joueur1->setPion(&pion);
        tableau.addJoueur(joueur1);
        
    } else if (playerPion == "pion2") {
        pion.setCheminImage("assets/pion2.png");
        joueur1->setPion(&pion);
        tableau.addJoueur(joueur1);
    } else if (playerPion == "pion3") {
        pion.setCheminImage("assets/pion3.png");
        joueur1->setPion(&pion);
        tableau.addJoueur(joueur1);
    }

    Button rollButton("assets/roll.png");

    // Dimensions de la fenêtre
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    // Dimensions du bouton après ajustement
    float buttonWidth = rollButton.getSize().x * 0.2f;
    float buttonHeight = rollButton.getSize().y * 0.2f;

    // Décalages spécifiés
    float topOffset = 20.0f;
    float leftOffset = 1100.0f;
    float bottomOffset = 200.0f;
    float rightOffset = 45.0f;

    // Calcul des coordonnées en fonction des décalages
    float xPosition = leftOffset;
    float yPosition = topOffset;

    // Ajustement de la position en fonction de la taille du bouton
    xPosition = std::min(xPosition, windowWidth - rightOffset - buttonWidth);
    yPosition = std::min(yPosition, windowHeight - bottomOffset - buttonHeight);

    // Positionnement du bouton
    rollButton.setPosition(sf::Vector2f(xPosition, yPosition));

    rollButton.setScale(sf::Vector2f(0.2f, 0.2f));  // Ajustement de la taille

    std::vector<sf::Sprite> diceSprites;
    sf::Texture texture;
    if (!texture.loadFromFile("board.png")) {
        std::cout << "Erreur lors du chargement de l'image du dé." << std::endl;
    }
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Plateau de jeu");
    sf::Sprite sprite = sf::Sprite(texture);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            rollButton.handleEvent(event, window);

            if (rollButton.isClicked()) {
                diceSprites = tableau.initializeDiceSprites(des, rollButton.getPosition(), position, points, *joueur1, window);
                rollButton.resetClicked();
            }
        }

        window.clear();
        window.draw(sprite);
        for (size_t i = 0; i < diceSprites.size(); ++i) {
            window.draw(diceSprites[i]);
        }

        for (size_t i = 0; i < points.size(); ++i) {
            sf::CircleShape point(2.0f);
            point.setPosition(points[i]);
            point.setFillColor(sf::Color::Red);
            window.draw(point);
        }

        pion.afficher(window);
        rollButton.draw(window);

        window.display();
    }
}

    return 0;
}
