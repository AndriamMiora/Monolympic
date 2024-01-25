#pragma once 
# include <string>
# include <iostream>
# include <vector>
# include "joueur.hpp"
# include "Pion.hpp"
# include "case.hpp"
// classe pour gérer les joueurs bots
class BotJoueur : public Joueur {

public : 
    // constructeur
    BotJoueur(Pion* pion, int points, std::vector<int>casesAchetees, bool isBot) : Joueur(pion, points, casesAchetees, isBot) {}

    // constructeur par défaut
    BotJoueur() : Joueur(nullptr, 20, std::vector<int>(), true) {}

    // simuler clic aléatoire si tombe sur une case quiz

    // simuler clic aléatoire (acheter ou non) si tombe sur une case propriété ou service public


    // simuler clic automatique sur bouton continuer

};



