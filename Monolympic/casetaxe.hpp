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
    CaseTaxe(int _montant, int position) : Case(position), montant(_montant) {} // constructeur avec paramètres

    CaseTaxe() : Case(4), montant(100) {} // Initialisation par défaut
    
     void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const override{ // méthode pour l'action de la case
        //std::cout << "Vous êtes sur une case de taxe. Vous devez payer " << montant << " médailles olympiques." << std::endl;
        if (J.getPoints() < montant) {
            //std::cout << "Vous n'avez pas assez de médailles pour payer la taxe" << std::endl;
            J.setPoints(0);
        } else {
            J.setPoints(J.getPoints() - montant);
        }
          
    }

    // Méthode pour obtenir le montant de la taxe
    int getMontant() const {
        return montant;
    }
};

