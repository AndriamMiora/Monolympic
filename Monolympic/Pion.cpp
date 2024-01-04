#include "Pion.hpp"
# include <iostream>

Pion::Pion(const std::string& cheminImage, sf::Vector2f position) {
    if (!texture.loadFromFile(cheminImage)) {
        // Gérer l'erreur de chargement de l'image
        std::cerr << "Erreur lors du chargement de l'image du pion." << std::endl;
        // Vous pouvez ajouter d'autres actions à effectuer en cas d'échec de chargement
    }

    sprite.setTexture(texture);

    // Redimensionner le sprite (ajuster ces valeurs selon vos besoins)
    float facteurRedimensionnement = 0.05f; // Exemple : réduire la taille de moitié
    sprite.setScale(facteurRedimensionnement, facteurRedimensionnement);

    sprite.setPosition(position);
}

void Pion::deplacerVers(sf::Vector2f nouvellePosition) {
    sprite.setPosition(nouvellePosition);
}

void Pion::afficher(sf::RenderWindow& window) {
    window.draw(sprite);
}