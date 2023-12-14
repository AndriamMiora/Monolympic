#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#pragma once

// Classe de base pour représenter une case du jeu
class Case {
public:
    virtual void action() const = 0;  // Fonction virtuelle
    virtual ~Case() = default;  // Destructeur virtuel
};
