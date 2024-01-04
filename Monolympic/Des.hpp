// Des.hpp
#pragma once
#include <vector>
#include <string>

class Des {
public:
    Des();
    int lancerDe();
    void lancerDes(int& de1, int& de2);
    std::vector<std::string> getDiceImages(int de1, int de2);

private:
    // Ajoutez les membres nécessaires
};
