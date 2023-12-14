#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <deque>
#include <map>

// Classe de base pour représenter une case du jeu
class Case {
public:
    virtual void action() const = 0;
    virtual ~Case() = default;
};

// Classe de base pour représenter une propriété
class Propriete : public Case {
protected:
    std::string nom;
    int prix;
    int loyer;
    std::string proprietaire;

public:
    Propriete(std::string _nom, int _prix, int _loyer) : nom(_nom), prix(_prix), loyer(_loyer), proprietaire("") {}

    void action() const override {
        std::cout << "Vous êtes sur la propriété : " << nom << std::endl;
    }

    virtual void afficherDetails() const {
        std::cout << "Nom : " << nom << ", Prix : " << prix << ", Loyer : " << loyer << std::endl;
    }

    virtual ~Propriete() = default;
};

// Classe pour représenter une propriété spécifique
class SiteOlympique : public Propriete {
public:
    SiteOlympique(std::string _nom, int _prix, int _loyer) : Propriete(_nom, _prix, _loyer) {}

    void action() const override {
        Propriete::action();
        if (proprietaire == "") {
            std::cout << "Cette propriété est à vendre." << std::endl;
        } else {
            std::cout << "Cette propriété appartient à " << proprietaire << ". Vous devez payer un loyer de " << loyer << " médailles olympiques." << std::endl;
        }
    }
};

// Classe représentant une carte "Chance" ou "CaisseCommunaute"
class Carte : public Case {
public:
    virtual void action() const override = 0;
    virtual ~Carte() = default;
};

// Classe pour représenter une carte "Chance"
class CarteChance : public Carte {
public:
    void action() const override {
        std::cout << "Vous piochez une carte Chance." << std::endl;
    }
};

// Classe pour représenter une carte "CaisseCommunaute"
class CarteCaisseCommunaute : public Carte {
public:
    void action() const override {
        std::cout << "Vous piochez une carte de la caisse de communauté." << std::endl;
    }
};

// Classe pour représenter un joueur
class Joueur {
private:
    std::string nom;
    int medailles;
    std::vector<Propriete*> proprietes;

public:
    Joueur(std::string _nom) : nom(_nom), medailles(0) {}

    void acheterPropriete(Propriete* propriete) {
        medailles -= propriete->getPrix();
        propriete->setProprietaire(nom);
        proprietes.push_back(propriete);
    }

    void afficherProprietes() const {
        std::cout << nom << " possède les propriétés suivantes : " << std::endl;
        for (const auto& prop : proprietes) {
            prop->afficherDetails();
        }
    }

    ~Joueur() {
        for (auto prop : proprietes) {
            delete prop;
        }
    }
};

// Classe pour représenter le jeu
class MonopolyOlympique {
private:
    std::vector<Case*> plateau;
    std::vector<Joueur*> joueurs;
    std::deque<Carte*> cartesChance;
    std::map<std::string, std::vector<std::string>> questionsQuiz;

public:
    MonopolyOlympique() {
        // Initialisation du plateau
        // Ajoutez des instances de SiteOlympique, CarteChance, et CarteCaisseCommunaute
        // au plateau en fonction de votre conception spécifique

        // Initialisation des joueurs
        // Ajoutez autant de joueurs que nécessaire

        // Initialisation des cartes Chance
        // Ajoutez autant de cartes que nécessaire
        cartesChance.push_back(new CarteChance());
        cartesChance.push_back(new CarteChance());
        // ...

        // Initialisation des questions du quiz
        questionsQuiz["Quelle ville a accueilli les Jeux Olympiques en 2008 ?"] = {"Beijing", "Londres", "Rio de Janeiro", "Athènes"};
        questionsQuiz["Qui est le plus grand champion olympique de tous les temps ?"] = {"Usain Bolt", "Michael Phelps", "Simone Biles", "Jesse Owens"};
        // Ajoutez plus de questions si nécessaire
    }

    ~MonopolyOlympique() {
        for (auto c : plateau) {
            delete c;
        }
        for (auto j : joueurs) {
            delete j;
        }
        for (auto carte : cartesChance) {
            delete carte;
        }
    }

    void tourDeJeu() {
        // Logique pour un tour de jeu
        // Utilisez les fonctions virtuelles pour appeler les actions spécifiques à chaque type de case
    }

    void afficherPlateau() const {
        for (const auto& c : plateau) {
            c->action();
        }
    }

    void poserQuestionQuiz(Joueur* joueur) {
        // Logique pour poser une question du quiz et ajuster les médailles du joueur
    }

    // Ajoutez d'autres fonctions et surcharges d'opérateurs si nécessaire
};
