#pragma once
#include <vector>
#include "joueur.hpp"
// Création d'un type Point pour les coordonnées


class Case {
protected:
    // Position d'une carte qui est un int 
    int position;

public:
    // Constructeur
    Case(int position) : position(position) {} 

    // constructeur par défaut
    Case() = default;

    // Fonction virtuelle pure
    virtual void action(Joueur& J, sf::RenderWindow& window,std::vector<sf::Vector2f> points) const = 0;
    
    // fonction virtuelle pas pure getCout
    virtual int getCout() const {
        return 0;
    }

    // fonction virtuelle pas pure actionBot
    virtual void actionbot(Joueur& J, sf::RenderWindow& window,std::vector<sf::Vector2f> points, int number1 , int number2 ) const {
        return;
    }
    

 
    // Getter pour les coordonnées
    int getPosition() const {
        return position;
    }

    // Destructeur virtuel
    virtual ~Case() = default;
};
