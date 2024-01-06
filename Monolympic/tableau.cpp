#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "tableau.hpp"




// fonction de get points
std::vector<sf::Vector2f> Tableau::getPoints() {
sf::Texture texture;
sf::RenderWindow window(sf::VideoMode(1280, 720), "Plateau de jeu");

sf::Sprite sprite;

   if (!texture.loadFromFile("board.png")) {
        std::cerr << "Erreur lors du chargement de l'image du plateau" << std::endl;
    }

    sprite.setTexture(texture);

    sf::Vector2i caseNormaleSize(49, 84);
    sf::Vector2i caseNormaleRotateSize(84, 49);
    sf::Vector2i caseDepartSize(85, 84);

    float offsetY = -138.0f;
    float offsetYTop = 57.0f;

    float basImage = static_cast<float>(texture.getSize().y);
    float hautImage = 0.0f;

    std::vector<sf::Vector2f> positions;
    std::vector<sf::Vector2f> points;

    sf::Vector2f positionDepartGauche(310.0f, basImage + offsetY);
    sf::Vector2f positionDepartDroite(positionDepartGauche.x + 10.6 * caseNormaleSize.x, positionDepartGauche.y);

    positions.push_back(positionDepartDroite);

    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartDroite.x - caseNormaleSize.x * (i + 1), positionDepartDroite.y);
        positions.push_back(position);
    }

    positions.push_back(positionDepartGauche);

    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartGauche.x - caseNormaleRotateSize.x, positionDepartGauche.y - caseNormaleRotateSize.y * (i + 1));
        positions.push_back(position);
    }

    sf::Vector2f positionDepartGaucheTop(positionDepartGauche.x, hautImage + offsetYTop);
    positions.push_back(positionDepartGaucheTop);

    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartGaucheTop.x + caseDepartSize.x + (caseNormaleSize.x * i), positionDepartGaucheTop.y);
        positions.push_back(position);
    }

    sf::Vector2f positionDepartDroiteTop(positions.back().x + caseNormaleSize.x, positionDepartGaucheTop.y);
    positions.push_back(positionDepartDroiteTop);

    for (int i = 8; i >= 0; --i) {
        sf::Vector2f position(positionDepartDroite.x + caseNormaleRotateSize.x, positionDepartDroite.y - caseNormaleRotateSize.y * (i + 1));
        positions.push_back(position);
    }

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
            //printf("Point : %zu (%f, %f)\n", i, point.getPosition().x, point.getPosition().y);
        } else {
            point.setPosition(positions[i] + sf::Vector2f(caseShape.getSize().x / 2.0f, caseShape.getSize().y / 2.0f));
            point.move(caseNormaleRotateSize.x, 0.0f);
            points.push_back(point.getPosition());
            //printf("Point : %zu (%f, %f)\n", i, point.getPosition().x, point.getPosition().y);
        }
    }
    return points;
}


std::vector<sf::Texture> diceTextures;

// Fonction pour initialiser les sprites des dés
std::vector<sf::Sprite> Tableau::initializeDiceSprites(Des& des, sf::Vector2f buttonPosition, int& position, std::vector<sf::Vector2f> points, Joueur& joueur) {
    int de1 = des.lancerDe();
    int de2 = des.lancerDe();
    int sommeDes = de1 + de2;
    if(position + sommeDes >= points.size()){
        joueur.setPoints(joueur.getPoints() + 200);
    }

    int nouvellePosition = (position + sommeDes) % points.size();
   
    joueur.getPion()->deplacerVers(points[nouvellePosition]);
    actionAtPosition(nouvellePosition);
    position = nouvellePosition;
    std::vector<sf::Sprite> diceSprites;
    // Charger les images des dés en dehors de la boucle principale
    std::vector<std::string> dicePaths = des.getDiceImages(de1, de2);
    diceSprites.clear();  // Vide le vecteur des sprites des dés
    diceTextures.clear();

    float xOffset = 25.0f;
    float yOffset = 110.0f;
    float spaceBetweenDice = 20.0f;
    float verticalMargin = 5.0f;
    float diceScaleFactor = 0.5f;


    for (size_t i = 0; i < dicePaths.size(); ++i) {
        sf::Texture texture;
        if (texture.loadFromFile(dicePaths[i])) {
            diceTextures.push_back(texture);
        }
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
        }

        //std::cout << "Chemin de l'image du dé " << i << " : " << dicePaths[i] << std::endl;
    }
    return diceSprites;
}


