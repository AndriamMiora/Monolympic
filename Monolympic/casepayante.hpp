#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#pragma once
#include <vector>
#include <string>
#include "joueur.hpp"

// Classe dérivée pour les cases chance
class CasePayante : public Case {
protected:
    int cout;
    mutable bool estAchete;
public:
    CasePayante(int _position, int _cout, bool _estAchete)
        : Case(_position),
          cout(_cout),
          estAchete(_estAchete) {} // Initialisation par défaut
    
};