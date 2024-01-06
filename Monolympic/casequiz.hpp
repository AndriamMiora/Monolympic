#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#pragma once
#include <vector>
#include <string>

// Classe dérivée pour les cases quiz
class CaseQuiz : public Case {
public:
    CaseQuiz(int _position) : Case(_position) {}

    void action() const override {
        std::cout << "Vous êtes sur une case Quiz (position " << getPosition() << "). Posez une question." << std::endl;
    }
};