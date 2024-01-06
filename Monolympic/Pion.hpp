// Pion.h
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Pion {
public:
    Pion(const std::string& cheminImage, sf::Vector2f position);
    void deplacerVers(sf::Vector2f nouvellePosition);
    void afficher(sf::RenderWindow& window);
    
    // Getters et setters
    
    // Position
    void setPosition(sf::Vector2f position) {
        this->position = position;
    }
    
    sf::Vector2f getPosition() const {
        return position;
    }
    
    // CheminImage
    const std::string& getCheminImage() const {
        return cheminImage;
    }

    void setCheminImage(const std::string& nouveauCheminImage) {
        cheminImage = nouveauCheminImage;
        if (!texture.loadFromFile(cheminImage)) {
            // Gérer l'erreur de chargement de l'image
            std::cout << "Erreur lors du chargement de l'image du pion." << std::endl;
            // Vous pouvez ajouter d'autres actions à effectuer en cas d'échec de chargement
        }
        sprite.setTexture(texture);
    }

private:
    sf::Vector2f position;
    std::string cheminImage;  // Pas de référence constante ici
    sf::Texture texture;
    sf::Sprite sprite;
};