#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Pion.hpp"
#include "Des.hpp"
#include "Button.hpp"
#pragma once
#include <vector>

class Tableau {
public:
    Tableau() = default;
    std::vector<sf::Vector2f> getPoints();
    std::vector<sf::Sprite> initializeDiceSprites(Des& des, sf::Vector2f buttonPosition, int& position, std::vector<sf::Vector2f> points, Pion& pion);
};
