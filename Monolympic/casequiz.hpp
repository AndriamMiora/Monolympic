#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#pragma once
#include <vector>
#include <string>
#include "joueur.hpp"
// Classe dérivée pour les cases quiz
class CaseQuiz : public Case {
public:
    CaseQuiz(int _position) : Case(_position) {}

    void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const override{
        std::cout << "Vous êtes sur une case Quiz (position " << getPosition() << "). Posez une question." << std::endl;
    }
};