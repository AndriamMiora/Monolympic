#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

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
    introScreenTexture.loadFromFile("font.jpeg");
    introScreen.setTexture(&introScreenTexture);

    // Pour afficher du texte
    sf::Text introScreenText;
    introScreenText.setFont(stdFont);
    introScreenText.setCharacterSize(50);
    introScreenText.setPosition(sf::Vector2f(50.0f, 600.0f));
    // Position du texte en bas à gauche de la fenêtre
    introScreenText.setFillColor(sf::Color::White);
    introScreenText.setString("MONOLYMPIC GAMES");


    sf::Text introScreenText2;
    introScreenText2.setFont(stdFont);
    introScreenText2.setCharacterSize(20);
    introScreenText2.setPosition(sf::Vector2f(10.0f, 10.0f));
    introScreenText2.setFillColor(sf::Color::Black);
    introScreenText2.setString("by Andrianarivo Ashley & Andriambolo-nivo Miora\n");

    // créer un bouton pour commencer le jeu
    sf::Texture newGameButtonTexture;
    newGameButtonTexture.loadFromFile("assets/Start.png");
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
    selectionScreenTexture.loadFromFile("assets/selection-screen.png");
    sf::RectangleShape selectionScreen(sf::Vector2f(1280.0f, 720.0f));
    selectionScreen.setTexture(&selectionScreenTexture);

    // créer un bouton pour entrer le nom du joueur
    sf::Texture enternametexture;
    enternametexture.loadFromFile("assets/entrer_nom.png");
    sf::RectangleShape enternamebutton(sf::Vector2f(316.0f, 94.0f));
    enternamebutton.setTexture(&enternametexture);
    enternamebutton.setPosition(sf::Vector2f(480.0f, 210.0f));
 
    // box pour entrer le nom du joueur
    sf::RectangleShape nameInputBox(sf::Vector2f(300.0f, 50.0f));
    nameInputBox.setFillColor(sf::Color::White);
    nameInputBox.setPosition(sf::Vector2f(480.0f, 300.0f));

    // texte pour entrer le nom du joueur
    sf::Text nameInputText;
    nameInputText.setFont(stdFont);
    nameInputText.setCharacterSize(20);
    nameInputText.setPosition(sf::Vector2f(480.0f, 300.0f));
    nameInputText.setFillColor(sf::Color::Black); // Définir la couleur du texte en noir

    // Ajout bouton pour valider le nom du joueur
    sf::Texture validatetexture;
    validatetexture.loadFromFile("assets/validate.png");
    sf::RectangleShape validatebutton(sf::Vector2f(316.0f, 94.0f));
    validatebutton.setTexture(&validatetexture);
    validatebutton.setPosition(sf::Vector2f(480.0f, 350.0f));
    

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
            window.draw(nameInputBox);
            window.draw(nameInputText);
            window.draw(enternamebutton);
            window.draw(validatebutton);
            window.display();
        }
    }

    // Choix du pions : 4 choix de pions

    sf::Texture pion1texture;
    pion1texture.loadFromFile("assets/player1.png");
    sf::RectangleShape pion1(sf::Vector2f(50.0f, 50.0f));
    pion1.setTexture(&pion1texture);
    pion1.setPosition(sf::Vector2f(480.0f, 400.0f));

    sf::Texture pion2texture;
    pion2texture.loadFromFile("assets/player2.png");
    sf::RectangleShape pion2(sf::Vector2f(50.0f, 50.0f));
    pion2.setTexture(&pion2texture);
    pion2.setPosition(sf::Vector2f(480.0f, 450.0f));

    sf::Texture pion3texture;
    pion3texture.loadFromFile("assets/player3.png");
    sf::RectangleShape pion3(sf::Vector2f(50.0f, 50.0f));
    pion3.setTexture(&pion3texture);
    pion3.setPosition(sf::Vector2f(480.0f, 500.0f));

   

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
        window.draw(pion1);
        window.draw(pion2);
        window.draw(pion3);

        window.display();
    }
}

// Code pour la deuxième boucle (affichage du plateau de jeu)
if (gameStarted) {
    sf::Texture boardtexture;
    boardtexture.loadFromFile("Board.jpeg");
    sf::RectangleShape board(sf::Vector2f(1280.0f, 720.0f));
    board.setTexture(&boardtexture);

    bool boardSelected = false;
    string playerBoard = "";
    while (!boardSelected && window.isOpen()) {
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
            if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (board.getGlobalBounds().contains(mousePos)) {
                    boardSelected = true;
                    playerBoard = "board";
                }
            }
        }

        window.clear();
        window.draw(board);
        // afficher le pion du joueur en bas à droite du plateau
        if (playerPion == "pion1") {
            pion1.setPosition(sf::Vector2f(1000.0f, 400.0f));
            window.draw(pion1);
        }
        if (playerPion == "pion2") {
            pion2.setPosition(sf::Vector2f(1000.0f, 400.0f));
            window.draw(pion2);
        }
        if (playerPion == "pion3") {
            pion3.setPosition(sf::Vector2f(1000.0f, 400.0f));
            window.draw(pion3);
        }
    
        window.display();
    }
}

window.clear();
window.close();
return 0;
}