#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#include <string.h>
#pragma once
#include <vector>
#include "joueur.hpp"

// Classe dérivée pour les cases fermeture ville
class CaseFermetureVille : public Case {
public:
    CaseFermetureVille(int _position) : Case(_position) {}

    void action(Joueur& j) const override {
        std::cout << "Vous êtes sur une case de fermeture de ville (position " << getPosition() << ")." << std::endl;
    }
};