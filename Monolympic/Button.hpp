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
  

    // Récupérer les dimensions de la fenêtre

    std::pair<float, float> createRollButton(const std::string& texturePath, const sf::RenderWindow& window) {

    Button rollButton(texturePath);
   
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

  
    return std::make_pair(xPosition, yPosition);
}

    Button(const std::string& imagePath);
    Button(const std::string& imagePath, const sf::Vector2f& position);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    bool clicked;
};
