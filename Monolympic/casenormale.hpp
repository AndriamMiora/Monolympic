#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#include <string.h>
#pragma once
#include <vector>
#include "joueur.hpp"
// Classe dérivée pour les cases normales
class CaseNormale : public Case {
public:
    CaseNormale(int _position) : Case(_position) {}

    void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const override{
        std::cout << "Vous êtes sur une case normale (position " << getPosition() << "). Rien ne se passe ici." << std::endl;
    }
};