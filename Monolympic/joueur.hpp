#pragma once 
# include <string>
# include <iostream>
# include <vector>
# include "Pion.hpp"

class Joueur {

private:
    // Pion du joueur
    Pion* pion;

    // Nombre de points du joueur
    int points;

    

public:

    // Constructeur avec initialisation du pion
    Joueur(Pion* pion, int points) : pion(pion), points(points) {}

    // Constructeur par défaut
    Joueur() : pion(nullptr), points(0) {}

    // Getter pour le pion
    Pion* getPion() const {
        return pion;
    }

    // Getter pour les points
    int getPoints() const {
        return points;
    }

    // Setter pour les points
    void setPoints(int points) {
        this->points = points;
    }

    // Setter pour le pion
    void setPion(Pion* pion) {
        this->pion = pion;
    }
    
    // Destructeur
    ~Joueur() {
        // Libérer la mémoire du pion si nécessaire
        delete pion;
    }
};

