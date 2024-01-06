
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#include "joueur.hpp"
#pragma once
#include <vector>
// Classe dérivée pour les cases propriété
class CasePropriete : public Case {
public:
    CasePropriete(int _position, int _cout) : Case(_position), cout(_cout) {}

    void action(Joueur& j) const override {
        std::cout << "Vous êtes sur une case propriété (position " << getPosition() << ") avec un coût de " << cout << "." << std::endl;
    }

private:
    int cout;
};