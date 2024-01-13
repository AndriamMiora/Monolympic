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

    // vecteur avec la liste des positions des cases achetées par le joueur
    std::vector<int>casesAchetees;

public:

    // Constructeur avec initialisation du pion
    Joueur(Pion* pion, int points, std::vector<int>casesAchetees) : pion(pion), points(points), casesAchetees(casesAchetees) {}

    // Constructeur par défaut
    Joueur() : pion(nullptr), points(20), casesAchetees() {}

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
    
    // Getter pour les cases achetées
    std::vector<int> getCasesAchetees() const {
        return casesAchetees;
    }

    // Setter pour les cases achetées
    void setCasesAchetees(std::vector<int> casesAchetees) {
        this->casesAchetees = casesAchetees;
    }

    
    // Destructeur
    ~Joueur() {
        // Libérer la mémoire du pion si nécessaire
        delete pion;
    }
};

