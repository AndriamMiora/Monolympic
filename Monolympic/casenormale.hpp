#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#include <string.h>
#pragma once
#include <vector>

// Classe dérivée pour les cases normales
class CaseNormale : public Case {
public:
    CaseNormale(int _position) : Case(_position) {}

    void action() const override {
        std::cout << "Vous êtes sur une case normale (position " << getPosition() << "). Rien ne se passe ici." << std::endl;
    }
};