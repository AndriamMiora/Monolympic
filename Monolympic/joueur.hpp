#pragma once 
# include <string>
# include <iostream>
# include <vector>
# include "Pion.hpp"

class Joueur {

private:
    // Pion du joueur
    Pion* pion;

    // Nombre de points du joueur
    int points;

    // vecteur avec la liste des positions des cases achetées par le joueur
    std::vector<int>casesAchetees;

    mutable bool acarteouvertureville = false;

    mutable bool acartedispensequiz = false;

    mutable bool fermerVille = false;

    mutable bool isBot = false;

public:

    // Constructeur avec initialisation du pion
    Joueur(Pion* pion, int points, std::vector<int>casesAchetees, bool _bot) : pion(pion), points(points), casesAchetees(casesAchetees) , acarteouvertureville(false), acartedispensequiz(false) , fermerVille(false) , isBot(_bot) {}

    // Constructeur par défaut
    Joueur() : pion(nullptr), points(20), casesAchetees() , acarteouvertureville(false), acartedispensequiz(false) , fermerVille(false) , isBot(false) {}

    // Getter pour le pion
    Pion* getPion() const {
        return pion;
    }

    // Getter pour le bot
    bool getBot() const {
        return isBot;
    }
    void setBot(bool _bot) {
        isBot = _bot;
    }
    // Getter pour les points
    int getPoints() const {
        return points;
    }

    // Getter pour la carte ouverture ville
    bool getCarteOuvertureVille() const {
        return acarteouvertureville;
    }

    // Setter pour la carte ouverture ville
    void setCarteOuvertureVille(bool acarteouvertureville) {
        this->acarteouvertureville = acarteouvertureville;
    }
    // Getter pour la carte dispense quiz
    bool getCarteDispenseQuiz() const {
        return acartedispensequiz;
    }


    bool getFermerVille() const {
        return fermerVille;
    }

    void setFermerVille(bool fermerVille) {
        this->fermerVille = fermerVille;
    }

    // Setter pour la carte dispense quiz
    void setCarteDispenseQuiz(bool acartedispensequiz) {
        this->acartedispensequiz = acartedispensequiz;
    }

    // Setter pour les points
    void setPoints(int points) {
        this->points = points;
    }

    // Setter pour le pion
    void setPion(Pion* pion) {
        this->pion = pion;
    }
    
    // Getter pour les cases achetées
    std::vector<int> getCasesAchetees() const {
        return casesAchetees;
    }

    // Setter pour les cases achetées
    void setCasesAchetees(std::vector<int> casesAchetees) {
        this->casesAchetees = casesAchetees;
    }
    // surcharge de l'opérateur ==
bool operator==(const Joueur& joueur) const {
    return (this->getPoints() == joueur.getPoints());
}

// surcharge de l'opérateur <
bool operator<(const Joueur& joueur) const {
    return (this->getPoints() < joueur.getPoints());
}

// surcharge de l'opérateur >
bool operator>(const Joueur& joueur) const {
    // Utilisez l'opérateur < pour la comparaison, il n'est pas nécessaire de redéfinir l'opérateur >
    return joueur < *this;
}


    // Destructeur
    ~Joueur() {
        // Libérer la mémoire du pion si nécessaire
        delete pion;
    }
};

