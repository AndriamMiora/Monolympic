#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Pion.hpp"
#include "Des.hpp"
#include "Button.hpp"

int main() {
    sf::Texture texture;
    if (!texture.loadFromFile("board.png")) {
        std::cerr << "Erreur lors du chargement de l'image." << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Plateau de jeu");

    sf::Sprite sprite(texture);

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
            printf("Point : %zu (%f, %f)\n", i, point.getPosition().x, point.getPosition().y);
        } else {
            point.setPosition(positions[i] + sf::Vector2f(caseShape.getSize().x / 2.0f, caseShape.getSize().y / 2.0f));
            point.move(caseNormaleRotateSize.x, 0.0f);
            points.push_back(point.getPosition());
            printf("Point : %zu (%f, %f)\n", i, point.getPosition().x, point.getPosition().y);
        }
    }

    Pion pion("assets/pion2.png", sf::Vector2f(871.900024, 624.000000));  // Position initiale modifiée
    Button rollButton("assets/roll.png");
        // Dimensions de la fenêtre
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    // Dimensions du bouton après ajustement
    float buttonWidth = rollButton.getSize().x * 0.2f;
    float buttonHeight = rollButton.getSize().y * 0.2f;

    // Décalages spécifiés
   float topOffset = 20.0f;
    float leftOffset = 1100.0f;
    float bottomOffset = 200.0f;
    float rightOffset = 45.0f;

    // Calcul des coordonnées en fonction des décalages
    float xPosition = leftOffset;
    float yPosition = topOffset;

    // Ajustement de la position en fonction de la taille du bouton
    xPosition = std::min(xPosition, windowWidth - rightOffset - buttonWidth);
    yPosition = std::min(yPosition, windowHeight - bottomOffset - buttonHeight);

    // Positionnement du bouton
    rollButton.setPosition(sf::Vector2f(xPosition, yPosition));

    rollButton.setScale(sf::Vector2f(0.2f, 0.2f));  // Ajustement de la taille
    Des des;
    std::vector<sf::Sprite> diceSprites;
    int position = 0;
    std::vector<sf::Texture> diceTextures;

while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        rollButton.handleEvent(event, window);
    }

    if (rollButton.isClicked()) {
        int de1 = des.lancerDe();
        int de2 = des.lancerDe();
        int sommeDes = de1 + de2;
        int nouvellePosition = (position + sommeDes) % points.size();
        pion.deplacerVers(points[nouvellePosition]);
        position = nouvellePosition;

        std::cout << "Dé 1 : " << de1 << std::endl;
        std::cout << "Dé 2 : " << de2 << std::endl;
        std::cout << "Somme des dés : " << sommeDes << std::endl;

        // Charger les images des dés en dehors de la boucle principale
        std::vector<std::string> dicePaths = des.getDiceImages(de1, de2);
        diceSprites.clear();
        diceTextures.clear(); // Ajout de cette ligne pour vider le vecteur de textures

        // Position des dés
        float xOffset = 25.0f;
        float yOffset = 110.0f;
        float spaceBetweenDice = 20.0f; // L'espace souhaité entre les dés
        float verticalMargin = 5.0f;    // L'espace souhaité au-dessus et en dessous de chaque dé
        float diceScaleFactor = 0.5f;   // L'échelle souhaitée (réduire la taille du dé)

        sf::Vector2f buttonPosition = rollButton.getPosition();

        // Créer et positionner les sprites des dés
        for (size_t i = 0; i < dicePaths.size(); ++i) {
            sf::Texture texture;
            if (texture.loadFromFile(dicePaths[i])) {
                diceTextures.push_back(texture);
            }
        }

        for (size_t i = 0; i < dicePaths.size(); ++i) {
            if (diceTextures[i].loadFromFile(dicePaths[i])) {
                sf::Sprite diceSprite(diceTextures[i]);

                // Ajustez la taille des dés en modifiant l'échelle
                diceSprite.setScale(diceScaleFactor, diceScaleFactor);

                // Ajustez les coordonnées pour espacer les dés horizontalement
                diceSprite.setPosition(buttonPosition.x + xOffset, buttonPosition.y + yOffset + verticalMargin);

                diceSprites.push_back(diceSprite);

                // Augmentez xOffset pour ajouter un espace entre les dés
                xOffset += diceSprite.getGlobalBounds().width + spaceBetweenDice;
            } else {
                std::cerr << "Erreur lors du chargement de l'image du dé " << i << std::endl;
            }

            // Ajoutez ces lignes pour voir les chemins réels des images
            std::cout << "Chemin de l'image du dé " << i << " : " << dicePaths[i] << std::endl;
        }

        rollButton.resetClicked();
    }

    window.clear();
    window.draw(sprite);
    // Draw the dice sprites

    for (size_t i = 0; i < diceSprites.size(); ++i) {
        window.draw(diceSprites[i]);
    }

    for (size_t i = 0; i < points.size(); ++i) {
        sf::CircleShape point(2.0f);
        point.setPosition(points[i]);
        point.setFillColor(sf::Color::Red);
        window.draw(point);
    }

    pion.afficher(window);
    rollButton.draw(window);

    window.display();
}

    return 0;
}