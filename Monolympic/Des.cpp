// Des.cpp
#include "Des.hpp"

Des::Des() {
    // Initialiser la graine pour la génération de nombres aléatoires
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

int Des::lancerDe() {
    // Générer un nombre aléatoire entre 1 et 6
    // rand time null : pour que le nombre aléatoire change à chaque fois
    return (std::rand() % 6) + 1;
}

void Des::lancerDes(int& de1, int& de2) { // on lance les deux dés
    de1 = lancerDe(); // on lance le premier dé pour obtenir un nombre aléatoire entre 1 et 6
    de2 = lancerDe(); // on lance le deuxième dé pour obtenir un nombre aléatoire entre 1 et 6
} 

std::vector<std::string> Des::getDiceImages(int de1, int de2) { // on récupère les images des dés
    std::vector<std::string> diceImages;
    diceImages.push_back("assets/dice_" + std::to_string(de1) + ".png");
    diceImages.push_back("assets/dice_" + std::to_string(de2) + ".png");
    return diceImages;
}
