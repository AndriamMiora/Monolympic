#pragma once
#include "case.hpp"

class CaseDepart : public Case {
private:
    int nbmedailles;

public:
    // Constructeur avec des coordonnées spécifiques et le nombre de médailles
    CaseDepart(int _nbmedailles, Point _coordonnees) : Case(_coordonnees), nbmedailles(_nbmedailles) {}

    // Getter pour le nombre de médailles
    int getNbMedailles() const { return nbmedailles; }

    // Implémentation de la fonction virtuelle pure
    void action() const override {
        std::cout << "Vous êtes sur la case Départ (position " << coordonnees.x << ", " << coordonnees.y
                  << "). Vous recevez " << nbmedailles << " médailles olympiques." << std::endl;
    }
};
