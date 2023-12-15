#pragma once
#include "case.hpp"


// Classe pour représenter une case de compagnie de service public
class CaseServicePublic : public Case {
protected:
    std::string nom;

public:
    CaseServicePublic(std::string _nom) : nom(_nom) {}

    void action() const override {
        std::cout << "Vous êtes sur la case " << nom << "." << std::endl;
    }
};