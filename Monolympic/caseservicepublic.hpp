#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#pragma once
#include <vector>
#include <string>
#include "joueur.hpp"
// Classe dérivée pour les cases service public
class CaseServicePublic : public Case {
public:
    CaseServicePublic(int _position, const std::string& _type) : Case(_position), type(_type) {}

    void action(Joueur& J, sf::RenderWindow& window) const override{
        std::cout << "Vous êtes sur une case de service public (position " << getPosition() << ") de type " << type << "." << std::endl;
    }

private:
    std::string type;
};
