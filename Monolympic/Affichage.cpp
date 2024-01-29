#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Affichage.hpp"

// dans le main on a besoin de : window, gameStarted, playerName, playerPion, tableau, joueur1, joueur2

std::tuple<bool, std::string> Affichage::setupIntroScreen(sf::RenderWindow& window) {
    sf::Font stdFont;
    stdFont.loadFromFile("police1.otf");

    sf::Image favicon;
    favicon.loadFromFile("assets/favicon.png");
    window.setIcon(314, 229, favicon.getPixelsPtr());

    sf::RectangleShape introScreen(sf::Vector2f(1280.0f, 720.0f));
    sf::Texture introScreenTexture;
    introScreenTexture.loadFromFile("large.png");
    introScreen.setTexture(&introScreenTexture);

    sf::Text introScreenText, introScreenText2;
    initializeText(introScreenText, stdFont, 50, sf::Vector2f(50.0f, 600.0f));
    initializeText(introScreenText2, stdFont, 20, sf::Vector2f(10.0f, 10.0f), sf::Color::Black, "by Andrianarivo Ashley & Andriambolo-nivo Miora\n");

    sf::Texture newGameButtonTexture;
    newGameButtonTexture.loadFromFile("assets/Start2.png");
    sf::RectangleShape newGameButton(sf::Vector2f(316.0f, 94.0f));
    newGameButton.setTexture(&newGameButtonTexture);
    newGameButton.setPosition(sf::Vector2f(480.0f, 210.0f));

    bool gameStarted = false;
    std::string playerName = "";

    while (!gameStarted) {
        handleIntroEvents(window, gameStarted, newGameButton, playerName);
        drawIntroElements(window, introScreen, introScreenText, introScreenText2, newGameButton);
    }
    return std::make_tuple(gameStarted, playerName);
}


sf::RectangleShape Affichage::createSelectionWindow(sf::RenderWindow& window, std::string& playerName, sf::Font stdFont, bool gameStarted) {
    sf::Texture selectionScreenTexture, enternametexture, validatetexture;
    selectionScreenTexture.loadFromFile("assets/background.png");
    sf::RectangleShape selectionScreen(sf::Vector2f(1280.0f, 720.0f)), enternamebutton(sf::Vector2f(500.0f, 500.0f)), nameInputBox(sf::Vector2f(300.0f, 50.0f)), validatebutton(sf::Vector2f(316.0f, 94.0f));
    selectionScreen.setTexture(&selectionScreenTexture);
    enternametexture.loadFromFile("assets/name.png");
    enternamebutton.setTexture(&enternametexture);
    float x = (window.getSize().x - enternamebutton.getSize().x) / 2.0f, y = (window.getSize().y - enternamebutton.getSize().y) / 2.0f;
    enternamebutton.setPosition(sf::Vector2f(x, y));
    nameInputBox.setFillColor(sf::Color::Black);
    nameInputBox.setPosition(sf::Vector2f(490.0f, 425.0f));
    sf::Text nameInputText;
    initializeText(nameInputText, stdFont, 20, sf::Vector2f((1200.0f - nameInputText.getGlobalBounds().width) / 2.0f, 440.0f - nameInputText.getGlobalBounds().height / 2.0f), sf::Color::White);
    validatetexture.loadFromFile("assets/valider.png");
    validatebutton.setTexture(&validatetexture);
    validatebutton.setPosition(sf::Vector2f(480.0f, 500.0f));
    if (gameStarted) {
        bool nameEntered = false;  
        while (!nameEntered) {
            handleSelectionEvents(window, nameEntered, playerName, nameInputText, validatebutton);
            drawSelectionElements(window, selectionScreen, enternamebutton, nameInputBox, nameInputText, validatebutton);
        }
        playerName = nameInputText.getString();
    }
    return selectionScreen;
}
std::string Affichage::selectPlayerPion(sf::RenderWindow& window) {
    sf::RectangleShape selectionScreen(sf::Vector2f(1280.0f, 720.0f));
    sf::Texture selectionScreenTexture;
    selectionScreenTexture.loadFromFile("assets/background.png");
    selectionScreen.setTexture(&selectionScreenTexture);
    sf::Sprite chooseImageSprite;
    sf::Texture chooseImageTexture;
    chooseImageTexture.loadFromFile("assets/chooseimage.png");
    chooseImageSprite.setTexture(chooseImageTexture);
    initializeChooseImageSprite(chooseImageSprite, window);
    // Choix du pions 
    sf::Texture pion1texture; pion1texture.loadFromFile("assets/pion.png");
    sf::RectangleShape pion1(sf::Vector2f(50.0f, 50.0f));
    pion1.setTexture(&pion1texture); pion1.setPosition(sf::Vector2f(580.0f, 440.0f));
    sf::Texture pion2texture; pion2texture.loadFromFile("assets/pion2.png");
    sf::RectangleShape pion2(sf::Vector2f(50.0f, 50.0f));
    pion2.setTexture(&pion2texture);pion2.setPosition(sf::Vector2f(580.0f + 60.0f, 440.0f));  // Ajout de 60.0f pour décaler le deuxième pion
    
    std::string playerPion = "";
    bool pionSelected = false;
    while (!pionSelected && window.isOpen()) {
        handlePionSelectionEvents(window, pionSelected, playerPion, pion1, pion2);
        drawPionSelectionElements(window, selectionScreen, chooseImageSprite, pion1, pion2);
    }
    return playerPion;
}



