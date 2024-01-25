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


// gère les affichages 
class Affichage {
public : 
sf::Sprite loadSprite(const std::string& imagePath) {
    sf::Texture texture;
    texture.loadFromFile(imagePath);
    return sf::Sprite(texture);
}

sf::Sprite createsprite(sf::RenderWindow& window, const std::string& imagePath) {
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


sf::Text createAndInitializeTimeText (sf :: Font font) {
    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(10.f, 10.f);  // Ajustez la position selon vos besoins
    return timeText;
}

sf::Text createAndInitializeText(const sf::Font& font, int characterSize, const sf::Color& fillColor, const sf::Vector2f& position, const std::string& text) {
    sf::Text textObject;
    textObject.setFont(font);
    textObject.setCharacterSize(characterSize);
    textObject.setFillColor(fillColor);
    textObject.setPosition(position);
    textObject.setString(text);

    return textObject;
}


};

