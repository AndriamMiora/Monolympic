#pragma once
#include <vector>
#include "case.hpp"
#include "casedepart.hpp"
#include "casetaxe.hpp"

class Board {
private:
    std::vector<std::unique_ptr<Case>> cases;

public:
    // Ajoute une case au plateau
    void addCase(std::unique_ptr<Case> nouvelleCase) {
        cases.push_back(std::move(nouvelleCase));
    }

    // Affiche les actions de toutes les cases du plateau
    void play() const {
        for (const auto& cas : cases) {
            cas->action();
        }
    }
};
