#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    // Charger l'image
    sf::Texture texture;
    if (!texture.loadFromFile("board.png")) {
        std::cerr << "Erreur lors du chargement de l'image." << std::endl;
        return 1;
    }

    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Plateau de jeu");

    // Créer un sprite pour afficher l'image
    sf::Sprite sprite(texture);

    // Définir les dimensions d'une case normale, d'une case normale tournée et d'une case de départ
    sf::Vector2i caseNormaleSize(49, 84);
    sf::Vector2i caseNormaleRotateSize(84, 49);
    sf::Vector2i caseDepartSize(85, 84);

    // Épaisseur du contour
    float contourThickness = 1.0f;

    // Déplacement vers le haut (138 pixels au-dessus du côté bas)
    float offsetY = -138.0f;

    // Déplacement vers le bas (57 pixels du côté haut)
    float offsetYTop = 57.0f;

    // Calculer la position du côté bas et haut de l'image
    float basImage = static_cast<float>(texture.getSize().y);
    float hautImage = 0.0f;

    // Tableau pour stocker les positions des cases
    std::vector<sf::Vector2f> positions;
    
    // Position de la case de départ à gauche en bas
    sf::Vector2f positionDepartGauche(310.0f, basImage + offsetY);
   

    // Ajouter la case de départ à gauche en bas au tableau
    positions.push_back(positionDepartGauche);

    // Calculer les positions des 9 cases normales en bas
    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartGauche.x + caseDepartSize.x + (caseNormaleSize.x * i), positionDepartGauche.y);
        positions.push_back(position);
    
    }

    // Position de la case de départ à droite en bas
    sf::Vector2f positionDepartDroite(positions.back().x + caseNormaleSize.x, positionDepartGauche.y);
    //afficherPosition("DepartDroiteDown", positionDepartDroite);

    // Ajouter la case de départ à droite en bas au tableau
    positions.push_back(positionDepartDroite);

    // Calculer les positions des 9 nouvelles cases normales à gauche, au-dessus de la case "DepartGaucheDown"
    for (int i = 0; i < 9; ++i) {
        // Décaler le début de la case vers la droite
        sf::Vector2f position(positionDepartGauche.x- caseNormaleRotateSize.x, positionDepartGauche.y - caseNormaleRotateSize.y * (i + 1));
        // je veux deplacer la case vers la droite sans changer la taille de la case
        positions.push_back(position);
        //afficherPosition("NormaleRotateLeft" + std::to_string(i + 1), position);
    }

    // Calculer les positions des 9 nouvelles cases normales à d¢roite, au-dessus de la case "DepartDroiteDown"
    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartDroite.x + caseNormaleRotateSize.x, positionDepartDroite.y - caseNormaleRotateSize.y * (i + 1));
        positions.push_back(position);
        //afficherPosition("NormaleRotateRight" + std::to_string(i + 1), position);
    }

    // Calculer la position de départ en haut
    sf::Vector2f positionDepartGaucheTop(positionDepartGauche.x, hautImage + offsetYTop);
   

    // Ajouter la case de départ à gauche en haut au tableau
    positions.push_back(positionDepartGaucheTop);

    // Calculer les positions des 9 cases normales en haut
    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartGaucheTop.x + caseDepartSize.x + (caseNormaleSize.x * i), positionDepartGaucheTop.y);
        positions.push_back(position);
        
    }

    // Position de la case de départ à droite en haut
    sf::Vector2f positionDepartDroiteTop(positions.back().x + caseNormaleSize.x, positionDepartGaucheTop.y);
   

    // Ajouter la case de départ à droite en haut au tableau
    positions.push_back(positionDepartDroiteTop);

        // Tableau pour stocker les positions des points
        std::vector<sf::Vector2f> points;   
    
        // Dessiner les cases avec des contours noirs et des points au centre
        for (size_t i = 0; i < positions.size(); ++i) {
            sf::RectangleShape caseShape;

            // Définir la position et la taille de la case
            caseShape.setPosition(positions[i]);
            if (positions[i] == positionDepartGauche || positions[i] == positionDepartDroite || positions[i] == positionDepartGaucheTop || positions[i] == positionDepartDroiteTop) {
                caseShape.setSize(sf::Vector2f(caseDepartSize.x, caseDepartSize.y));
          
            } else if (positions[i].x == positionDepartGauche.x - caseNormaleRotateSize.x) {
                // Cas des nouvelles cases normales tournées à 90 degrés à gauche
                // décaler le debut de la case vers la droite 
                caseShape.setPosition(positions[i].x + caseNormaleRotateSize.x, positions[i].y);
                caseShape.setSize(sf::Vector2f(caseNormaleRotateSize.x, caseNormaleRotateSize.y));
            
            } else if (positions[i].x == positionDepartDroite.x + caseNormaleRotateSize.x) {
                // Cas des nouvelles cases normales tournées à 90 degrés à droite
                caseShape.setSize(sf::Vector2f(-caseNormaleRotateSize.x, caseNormaleRotateSize.y));
                
            } else {
                // Cas des cases normales existantes
                caseShape.setSize(sf::Vector2f(caseNormaleSize.x, caseNormaleSize.y));
              
            }

            // Dessiner le point au centre de la case
            sf::CircleShape point(2.0f);

            if (positions[i].x != positionDepartGauche.x - caseNormaleRotateSize.x) {
                point.setPosition(positions[i] + sf::Vector2f(caseShape.getSize().x / 2.0f, caseShape.getSize().y / 2.0f));
                // recupérer les coordonnées du point
                points.push_back(point.getPosition());
                printf("Point : %zu (%f, %f)\n", i, point.getPosition().x, point.getPosition().y);
            } else {
                // décaler le point vers la droite
                point.setPosition(positions[i] + sf::Vector2f(caseShape.getSize().x / 2.0f, caseShape.getSize().y / 2.0f));
                point.move(caseNormaleRotateSize.x, 0.0f);
                // recupérer les coordonnées du point
                points.push_back(point.getPosition());
                printf("Point : %zu (%f, %f)\n", i, point.getPosition().x, point.getPosition().y);
            }
            
        }

       while (window.isOpen()) {
        // Gérer les événements
        sf::Event event;
        while (window.pollEvent(event)) {
            // Fermer la fenêtre si l'utilisateur le souhaite
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Effacer la fenêtre
        window.clear(sf::Color::White);

        // Dessiner le sprite
        window.draw(sprite);

        // desiner les points 
        for (size_t i = 0; i < points.size(); ++i) {
            sf::CircleShape point(2.0f);
            point.setPosition(points[i]);
            // changer la couleur du point
            point.setFillColor(sf::Color::Red);
            window.draw(point);
        }

        // Afficher le contenu de la fenêtre à l'écran
        window.display();
    }

    return 0;
}