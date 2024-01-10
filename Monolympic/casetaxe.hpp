#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#include <string.h>
#pragma once
#include <vector>
#include "joueur.hpp"

// Classe pour représenter une case de taxe
class CaseTaxe : public Case {
protected:
    int montant;

public:
    CaseTaxe(int _montant, int position) : Case(position), montant(_montant) {}

    CaseTaxe() : Case(4), montant(100) {}

    // plusieurs cases taxe avec des positions différentes
    
    void action(Joueur& J, sf::RenderWindow& window) const override{
        std::cout << "Vous êtes sur une case de taxe. Vous devez payer " << montant << " médailles olympiques." << std::endl;
        if (J.getPoints() < montant) {
            std::cout << "Vous n'avez pas assez de médailles pour payer la taxe. Vous êtes éliminé." << std::endl;
        } else {
            J.setPoints(J.getPoints() - montant);
        }
          
    }
};

