// Pion.h
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Pion {
public:
    Pion(const std::string& cheminImage, sf::Vector2f position, int pos); // constructeur avec paramètres
    Pion(){ 
        position = sf::Vector2f(0,0);
        pos = 0;
        cheminImage = "images/pion.png";
    }
    void deplacerVers(sf::Vector2f nouvellePosition); // déplacer le pion vers une nouvelle position
    void afficher(sf::RenderWindow& window); // afficher le pion sur la fenêtre de jeu
    
    // Getters et setters
    
    // Position sur la fenêtre de jeu

    sf::Vector2f getPosition() const {
        return position;
    }
    void setPosition(sf::Vector2f position) {
        this->position = position;
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

    // Position sur le plateau
    int getPos() const {
        return pos;
    }

    void setPos(int pos) {
        this->pos = pos;
    }

    

private:
    sf::Vector2f position; // Position sur la fenêtre de jeu (en pixels)
    int pos; // Position sur le plateau de jeu
    std::string cheminImage;   // Chemin vers l'image du pion
    sf::Texture texture;      // Texture du pion
    sf::Sprite sprite;       // Sprite du pion
}; 