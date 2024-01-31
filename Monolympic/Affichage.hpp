#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Pion.hpp"
#include "Des.hpp"
#include "Button.hpp"
#include "case.hpp"
#include "casechance.hpp"
#include "casedepart.hpp"
#include "casefermeture.hpp"
#include "casenormale.hpp"
#include "casepropriete.hpp"
#include "casequiz.hpp"
#include "caseservicepublic.hpp"
#include "casetaxe.hpp"
#include "joueur.hpp"
#include "casepayante.hpp"
#include "tableau.hpp"
#include <utility>
#pragma once
#include <vector>


// gère les affichages de l'écran de jeu
class Affichage {
public : 
sf::Sprite loadSprite(const std::string& imagePath) { // charge une image et la transforme en sprite
    sf::Texture texture;
    texture.loadFromFile(imagePath);
    return sf::Sprite(texture);
}

sf::Sprite createsprite(sf::RenderWindow& window, const std::string& imagePath) { // charge une image et la transforme en sprite
    sf::Texture tourTexture;
    tourTexture.loadFromFile(imagePath);
    sf::Sprite tourSprite;
    tourSprite.setTexture(tourTexture);
    tourSprite.setOrigin(tourTexture.getSize().x / 2.0f, tourTexture.getSize().y / 2.0f);
    tourSprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    tourSprite.setScale(1.0f, 1.0f);

    return tourSprite;
}
std::tuple<bool, std::string>  setupIntroScreen(sf::RenderWindow& window);
sf::RectangleShape createSelectionWindow(sf::RenderWindow& window, std::string& playerName, sf :: Font stdFont, bool gameStarted);
std::string selectPlayerPion(sf::RenderWindow& window);


sf::Text createAndInitializeTimeText (sf :: Font font) {  // crée et initialise le texte du temps
    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(10.f, 10.f);  
    return timeText;
}

// Fonction auxiliaire pour initialiser un texte
sf::Text createAndInitializeText(const sf::Font& font, int characterSize, const sf::Color& fillColor, const sf::Vector2f& position, const std::string& text) {
    sf::Text textObject;
    textObject.setFont(font);
    textObject.setCharacterSize(characterSize);
    textObject.setFillColor(fillColor);
    textObject.setPosition(position);
    textObject.setString(text);
    return textObject;
}
// Fonction auxiliaire pour initialiser un texte
void initializeText(sf::Text& text, const sf::Font& font, int characterSize, const sf::Vector2f& position, const sf::Color& fillColor = sf::Color::White, const std::string& content = "") {
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setPosition(position);
    text.setFillColor(fillColor);
    text.setString(content);
}

// Fonction auxiliaire pour gérer les événements de l'écran d'introduction
void handleIntroEvents(sf::RenderWindow& window, bool& gameStarted, const sf::RectangleShape& newGameButton, std::string& playerName) {
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
}
// Fonction auxiliaire pour gérer les événements de la fenêtre d'entrée du nom
void handleSelectionEvents(sf::RenderWindow& window, bool& nameEntered, std::string& playerName, sf::Text& nameInputText, const sf::RectangleShape& validatebutton) {
    sf::Event evt;
    while (window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
            window.close();
        }
        if (evt.type == sf::Event::TextEntered) {
            handleTextEnteredEvent(evt, playerName, nameInputText);
        }
        if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
            handleMouseButtonPressedEvent(evt, window, nameEntered, playerName, nameInputText, validatebutton);
        }
    }
}

// Fonction auxiliaire pour gérer les événements de texte entré
void handleTextEnteredEvent(const sf::Event& evt, std::string& playerName, sf::Text& nameInputText) {
    if (evt.text.unicode >= 32 && evt.text.unicode <= 126) {
        playerName += static_cast<char>(evt.text.unicode);
        nameInputText.setString(playerName);
    } else if (evt.text.unicode == 8 && playerName.length() > 0) {
        playerName.pop_back();
        nameInputText.setString(playerName);
    }
}

// Fonction auxiliaire pour gérer les événements de clic de souris
void handleMouseButtonPressedEvent(const sf::Event& evt, sf::RenderWindow& window, bool& nameEntered, std::string& playerName, sf::Text& nameInputText, const sf::RectangleShape& validatebutton) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (validatebutton.getGlobalBounds().contains(mousePos)) {
        nameEntered = true;
    }
}

// Fonction auxiliaire pour dessiner les éléments de la fenêtre de sélection
void drawSelectionElements(sf::RenderWindow& window, const sf::RectangleShape& selectionScreen, const sf::RectangleShape& enternamebutton, const sf::RectangleShape& nameInputBox, const sf::Text& nameInputText, const sf::RectangleShape& validatebutton) {
    window.clear();
    window.draw(selectionScreen);
    window.draw(enternamebutton);
    window.draw(nameInputBox);
    window.draw(nameInputText);
    window.draw(validatebutton);
    window.display();
}


// Fonction auxiliaire pour dessiner les éléments de l'écran d'introduction
void drawIntroElements(sf::RenderWindow& window, const sf::RectangleShape& introScreen, const sf::Text& introScreenText, const sf::Text& introScreenText2, const sf::RectangleShape& newGameButton) {
    window.clear();
    window.draw(introScreen);
    window.draw(introScreenText2);
    window.draw(introScreenText);
    window.draw(newGameButton);
    window.display();
}


// Fonction auxiliaire pour initialiser l'image de sélection
void initializeChooseImageSprite(sf::Sprite& chooseImageSprite, const sf::RenderWindow& window) {
    float imageX = (window.getSize().x - chooseImageSprite.getGlobalBounds().width) / 2.0f;
    float imageY = (window.getSize().y - chooseImageSprite.getGlobalBounds().height) / 2.0f;
    chooseImageSprite.setPosition(sf::Vector2f(imageX, imageY));
}


// Fonction auxiliaire pour gérer les événements de sélection de pion
void handlePionSelectionEvents(sf::RenderWindow& window, bool& pionSelected, std::string& playerPion, const sf::RectangleShape& pion1, const sf::RectangleShape& pion2) {
    sf::Event evt;
    while (window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
            window.close();
        }
        if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            handlePionClickEvent(mousePos, pion1, pionSelected, playerPion, "pion1");
            handlePionClickEvent(mousePos, pion2, pionSelected, playerPion, "pion2");
        }
    }
}

// Fonction auxiliaire pour gérer les clics de pion
void handlePionClickEvent(const sf::Vector2f& mousePos, const sf::RectangleShape& pion, bool& pionSelected, std::string& playerPion, const std::string& pionType) {
    if (pion.getGlobalBounds().contains(mousePos)) {
        pionSelected = true;
        playerPion = pionType;
    }
}

// Fonction auxiliaire pour dessiner les éléments de sélection de pion
void drawPionSelectionElements(sf::RenderWindow& window, const sf::RectangleShape& selectionScreen, const sf::Sprite& chooseImageSprite, const sf::RectangleShape& pion1, const sf::RectangleShape& pion2) {
    window.clear();
    window.draw(selectionScreen);
    window.draw(chooseImageSprite);
    window.draw(pion1);
    window.draw(pion2);
    window.display();
}

// Fonction auxiliaire pour dessiner les éléments l'affichage du gagnant
void Drawgagner(sf::RenderWindow& window, sf::Sprite& gagner) {
    gagner.setOrigin(gagner.getTexture()->getSize().x / 2.0f, gagner.getTexture()->getSize().y / 2.0f);
    gagner.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    gagner.setScale(1.0f, 1.0f);
    window.draw(gagner);}
};

