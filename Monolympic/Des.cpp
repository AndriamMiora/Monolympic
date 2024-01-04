// Des.cpp
#include "Des.hpp"

Des::Des() {
    // Initialiser la graine pour la génération de nombres aléatoires
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

int Des::lancerDe() {
    // Générer un nombre aléatoire entre 1 et 6
    return (std::rand() % 6) + 1;
}

void Des::lancerDes(int& de1, int& de2) {
    de1 = lancerDe();
    de2 = lancerDe();
}

std::vector<std::string> Des::getDiceImages(int de1, int de2) {
    std::vector<std::string> diceImages;
    diceImages.push_back("assets/dice_" + std::to_string(de1) + ".png");
    diceImages.push_back("assets/dice_" + std::to_string(de2) + ".png");
    return diceImages;
}
