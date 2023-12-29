// Pion.h
#pragma once

#include <SFML/Graphics.hpp>

class Pion {
public:
    Pion(const std::string& cheminImage, sf::Vector2f position);
    void deplacerVers(sf::Vector2f nouvellePosition);
    void afficher(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};
