#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#pragma once
#include <vector>
#include <string>

// Classe dérivée pour les cases chance
class CaseChance : public Case {
public:
    CaseChance(int _position) : Case(_position) {}

    void action() const override {
        std::cout << "Vous êtes sur une case Chance (position " << getPosition() << ")." << std::endl;
    }
};