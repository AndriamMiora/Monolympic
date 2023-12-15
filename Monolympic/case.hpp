#pragma once

// Création d'un type Point pour les coordonnées
typedef struct {
    int x;
    int y;
} Point;

class Case {
protected:
    Point coordonnees;

public:
    // Constructeur par défaut
    Case() : coordonnees({0, 0}) {}

    // Constructeur avec des coordonnées spécifiques
    Case(Point _coordonnees) : coordonnees(_coordonnees) {}

    // Fonction virtuelle pure
    virtual void action() const = 0;

    // Getter pour les coordonnées
    Point getCoordonnees() const { return coordonnees; }

    // Destructeur virtuel
    virtual ~Case() = default;
};
