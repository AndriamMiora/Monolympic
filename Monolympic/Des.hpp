// Des.hpp
#pragma once
#include <vector>
#include <string>

class Des {
public:
    Des(); // constructeur par défaut
    int lancerDe(); // on lance le dé
    void lancerDes(int& de1, int& de2); // on lance les deux dés
    std::vector<std::string> getDiceImages(int de1, int de2); // on récupère les images des dés

private:
    // Ajoutez les membres nécessaires
};
