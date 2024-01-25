#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Affichage.hpp"

// dans le main on a besoin de : window, gameStarted, playerName, playerPion, tableau, joueur1, joueur2

std::tuple<bool, std::string> Affichage::setupIntroScreen(sf::RenderWindow& window) {

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
    std::string playerName = "";
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
    return std::make_tuple(gameStarted, playerName);
}


 sf::RectangleShape Affichage::createSelectionWindow(sf::RenderWindow& window, std::string& playerName, sf :: Font stdFont, bool gameStarted) {
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
         // Récupérer le nom entré par l'utilisateur
    playerName = nameInputText.getString();
    }
    // Retourner la fenêtre de sélection
    return selectionScreen;
}



std::string Affichage :: selectPlayerPion(sf::RenderWindow& window) {

    sf::Texture selectionScreenTexture;
    selectionScreenTexture.loadFromFile("assets/background.png");
    sf::RectangleShape selectionScreen(sf::Vector2f(1280.0f, 720.0f));
    selectionScreen.setTexture(&selectionScreenTexture);  

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
        pion1.setPosition(sf::Vector2f(580.0f, 440.0f));

        sf::Texture pion2texture;
        pion2texture.loadFromFile("assets/pion2.png");
        sf::RectangleShape pion2(sf::Vector2f(50.0f, 50.0f));
        pion2.setTexture(&pion2texture);
        pion2.setPosition(sf::Vector2f(580.0f + 60.0f, 440.0f));  // Ajout de 60.0f pour décaler le deuxième pion

        std :: string playerPion = "";

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
                }
            }
            window.clear();
            window.draw(selectionScreen);
            window.draw(chooseImageSprite);
            window.draw(pion1);
            window.draw(pion2);
            window.display();
        }

        return playerPion;
    }
