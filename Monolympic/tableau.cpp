#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "tableau.hpp"

// fonction de get points
std::vector<sf::Vector2f> Tableau::getPoints() {
   auto [positions, caseNormaleSize, caseNormaleRotateSize, caseDepartSize, positionDepartDroite, positionDepartGauche, 
  positionDepartGaucheTop,positionDepartDroiteTop] = initializePositions();

    std::vector<sf::Vector2f> points;

    for (size_t i = 0; i < positions.size(); ++i) {
        sf::RectangleShape caseShape;
        caseShape.setPosition(positions[i]);

        if (positions[i] == positionDepartGauche || positions[i] == positionDepartDroite || positions[i] == positionDepartGaucheTop || positions[i] == positionDepartDroiteTop) {
            caseShape.setSize(sf::Vector2f(caseDepartSize.x, caseDepartSize.y));
        } else if (positions[i].x == positionDepartGauche.x - caseNormaleRotateSize.x) {
            caseShape.setPosition(positions[i].x + caseNormaleRotateSize.x, positions[i].y);
            caseShape.setSize(sf::Vector2f(caseNormaleRotateSize.x, caseNormaleRotateSize.y));
        } else if (positions[i].x == positionDepartDroite.x + caseNormaleRotateSize.x) {
            caseShape.setSize(sf::Vector2f(-caseNormaleRotateSize.x, caseNormaleRotateSize.y));
        } else {
            caseShape.setSize(sf::Vector2f(caseNormaleSize.x, caseNormaleSize.y));
        }

        sf::CircleShape point(2.0f);

        if (positions[i].x != positionDepartGauche.x - caseNormaleRotateSize.x) {
            point.setPosition(positions[i] + sf::Vector2f(caseShape.getSize().x / 2.0f, caseShape.getSize().y / 2.0f));
            points.push_back(point.getPosition());
        } else {
            point.setPosition(positions[i] + sf::Vector2f(caseShape.getSize().x / 2.0f, caseShape.getSize().y / 2.0f));
            point.move(caseNormaleRotateSize.x, 0.0f);
            points.push_back(point.getPosition());
        }
    }
    return points;
}


std::vector<sf::Texture> diceTextures;

// Fonction pour initialiser les sprites des dés
std::pair<std::vector<sf::Sprite>, int> Tableau::initializeDiceSprites(Des& des, sf::Vector2f buttonPosition, int& position, std::vector<sf::Vector2f> points, Joueur* joueur, sf::RenderWindow& window) {
    int de1 = des.lancerDe(); int de2 = des.lancerDe();
    int sommeDes = de1 + de2;
    int nouvellePosition = (position + sommeDes) % points.size();
    joueur->getPion()->deplacerVers(points[nouvellePosition]);
    joueur->getPion()->setPos(nouvellePosition);
    if(position + sommeDes >= points.size()){
        joueur->setPoints(joueur->getPoints() + 20);
    }
    std::vector<sf::Sprite> diceSprites; std::vector<std::string> dicePaths = des.getDiceImages(de1, de2);
    diceSprites.clear(); diceTextures.clear();
    float xOffset = 25.0f; float yOffset = 110.0f;
    float spaceBetweenDice = 20.0f;
    float verticalMargin = 5.0f;
    float diceScaleFactor = 0.5f;
    for (size_t i = 0; i < dicePaths.size(); ++i) {
        sf::Texture texture;
        if (texture.loadFromFile(dicePaths[i])) {
            diceTextures.push_back(texture);}
    }
    for (size_t i = 0; i < dicePaths.size(); ++i) {
        if (diceTextures[i].loadFromFile(dicePaths[i])) {
            sf::Sprite diceSprite(diceTextures[i]);
            diceSprite.setScale(diceScaleFactor, diceScaleFactor);
            diceSprite.setPosition(buttonPosition.x + xOffset, buttonPosition.y + yOffset + verticalMargin);
            diceSprites.push_back(diceSprite);
            xOffset += diceSprite.getGlobalBounds().width + spaceBetweenDice;
        } else {
            std::cerr << "Erreur lors du chargement de l'image du dé " << i << std::endl;
        } }
     return std::make_pair(diceSprites, nouvellePosition);}

