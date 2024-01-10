#pragma once
#include "case.hpp"
#include <iostream>
#include "joueur.hpp"


class CaseDepart : public Case {
private:
    int nbmedailles;

public:
    // Constructeur avec des coordonnées spécifiques et le nombre de médailles
    CaseDepart(int _nbmedailles, int position) : Case(position), nbmedailles(_nbmedailles) {}

    // Constructeur par défaut
    CaseDepart() : Case(0), nbmedailles(2000) {}
    
    // Getter pour le nombre de médailles

    int getNbMedailles() const { return nbmedailles; }

    // Implémentation de la fonction virtuelle pure
    void action(Joueur& J, sf::RenderWindow& window) const override{
        std::cout << "Vous êtes sur la case Départ (position " << getPosition() << ") et vous gagnez " << getNbMedailles() << " médailles !" << std::endl;
        J.setPoints(J.getPoints() + getNbMedailles());
    }
};
