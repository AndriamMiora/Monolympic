// Button.cpp
#include "Button.hpp"
#include <iostream>  // Include for debugging purposes

Button::Button(const std::string& texturePath) : clicked(false) { 
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de l'image du bouton." << std::endl;
    }

    sprite.setTexture(texture);
}

void Button::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void Button::setScale(const sf::Vector2f& scale) {
    sprite.setScale(scale);
}

sf::Vector2f Button::getPosition() const {
    return sprite.getPosition();
}

sf::Vector2f Button::getSize() const {
    return sf::Vector2f(sprite.getGlobalBounds().width * sprite.getScale().x, sprite.getGlobalBounds().height * sprite.getScale().y);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::FloatRect bounds = sprite.getGlobalBounds();

        if (bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            clicked = true;
            // std::cout << "Button Clicked!" << std::endl;  
        }
    }
}

bool Button::isClicked() const {
    return clicked;
}

void Button::resetClicked() {
    clicked = false;
}
