// Button.hpp
#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
    void setPosition(const sf::Vector2f& position);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);  // Pass sf::RenderWindow as a parameter
    bool isClicked() const;
    void draw(sf::RenderWindow& window);
    void setScale(const sf::Vector2f& scale);
    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;
    void resetClicked();
    Button(const std::string& imagePath);
    Button(const std::string& imagePath, const sf::Vector2f& position);
private:
    sf::Texture texture;
    sf::Sprite sprite;
    bool clicked;
};
