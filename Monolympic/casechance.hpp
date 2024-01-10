#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#pragma once
#include <vector>
#include <string>
#include "joueur.hpp"

// Classe dérivée pour les cases chance
class CaseChance : public Case {
public:
    CaseChance(int _position) : Case(_position) {}

    void action(Joueur& J, sf::RenderWindow& window) const override{
        std::cout << "Vous êtes sur une case Chance (position " << getPosition() << ")." << std::endl;
        

    }
};