#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void afficherPosition(const std::string& nom, const sf::Vector2f& position) {
    std::cout << "Position de la case " << nom << " : (" << position.x << ", " << position.y << ")" << std::endl;
}

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
    afficherPosition("DepartGaucheDown", positionDepartGauche);

    // Ajouter la case de départ à gauche en bas au tableau
    positions.push_back(positionDepartGauche);

    // Calculer les positions des 9 cases normales en bas
    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartGauche.x + caseDepartSize.x + (caseNormaleSize.x * i), positionDepartGauche.y);
        positions.push_back(position);
        afficherPosition("NormaleDown" + std::to_string(i + 1), position);
    }

    // Position de la case de départ à droite en bas
    sf::Vector2f positionDepartDroite(positions.back().x + caseNormaleSize.x, positionDepartGauche.y);
    afficherPosition("DepartDroiteDown", positionDepartDroite);

    // Ajouter la case de départ à droite en bas au tableau
    positions.push_back(positionDepartDroite);

    // Calculer les positions des 9 nouvelles cases normales à gauche, au-dessus de la case "DepartGaucheDown"
    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartGauche.x- caseNormaleRotateSize.x, positionDepartGauche.y - caseNormaleRotateSize.y * (i + 1));
        positions.push_back(position);
        afficherPosition("NormaleRotateLeft" + std::to_string(i + 1), position);
    }

    // Calculer les positions des 9 nouvelles cases normales à droite, au-dessus de la case "DepartDroiteDown"
    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartDroite.x + caseNormaleRotateSize.x, positionDepartDroite.y - caseNormaleRotateSize.y * (i + 1));
        positions.push_back(position);
        afficherPosition("NormaleRotateRight" + std::to_string(i + 1), position);
    }

    // Calculer la position de départ en haut
    sf::Vector2f positionDepartGaucheTop(positionDepartGauche.x, hautImage + offsetYTop);
    afficherPosition("DepartGaucheTop", positionDepartGaucheTop);

    // Ajouter la case de départ à gauche en haut au tableau
    positions.push_back(positionDepartGaucheTop);

    // Calculer les positions des 9 cases normales en haut
    for (int i = 0; i < 9; ++i) {
        sf::Vector2f position(positionDepartGaucheTop.x + caseDepartSize.x + (caseNormaleSize.x * i), positionDepartGaucheTop.y);
        positions.push_back(position);
        afficherPosition("NormaleTop" + std::to_string(i + 1), position);
    }

    // Position de la case de départ à droite en haut
    sf::Vector2f positionDepartDroiteTop(positions.back().x + caseNormaleSize.x, positionDepartGaucheTop.y);
    afficherPosition("DepartDroiteTop", positionDepartDroiteTop);

    // Ajouter la case de départ à droite en haut au tableau
    positions.push_back(positionDepartDroiteTop);

    // Couleurs des cases
    sf::Color couleurCaseDepart(255, 0, 0); // Rouge
    sf::Color couleurCaseNormale(0, 255, 0); // Vert
    sf::Color couleurContour(0, 0, 0); // Noir
    sf::Color couleurPoint(0, 0, 255); // Bleu pour les points

    // Boucle principale de rendu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer l'écran
        window.clear();

        // Dessiner le sprite
        window.draw(sprite);

        // Dessiner les cases avec des contours noirs et des points au centre
        for (size_t i = 0; i < positions.size(); ++i) {
            sf::RectangleShape caseShape;

            // Définir la position et la taille de la case
            caseShape.setPosition(positions[i]);
            if (positions[i] == positionDepartGauche || positions[i] == positionDepartDroite || positions[i] == positionDepartGaucheTop || positions[i] == positionDepartDroiteTop) {
                caseShape.setSize(sf::Vector2f(caseDepartSize.x, caseDepartSize.y));
                caseShape.setFillColor(couleurCaseDepart);
            } else if (positions[i].x == positionDepartGauche.x - caseNormaleRotateSize.x) {
                // Cas des nouvelles cases normales tournées à 90 degrés à gauche
                caseShape.setSize(sf::Vector2f(caseNormaleRotateSize.x, caseNormaleRotateSize.y));
                caseShape.setFillColor(couleurCaseNormale);
            } else if (positions[i].x == positionDepartDroite.x + caseNormaleRotateSize.x) {
                // Cas des nouvelles cases normales tournées à 90 degrés à droite
                caseShape.setSize(sf::Vector2f(caseNormaleRotateSize.x, caseNormaleRotateSize.y));
                caseShape.setFillColor(couleurCaseNormale);
            } else {
                // Cas des cases normales existantes
                caseShape.setSize(sf::Vector2f(caseNormaleSize.x, caseNormaleSize.y));
                caseShape.setFillColor(couleurCaseNormale);
            }

            // Dessiner la case
            window.draw(caseShape);

            // Dessiner le contour noir
            sf::RectangleShape contourShape(caseShape.getSize() + sf::Vector2f(-contourThickness * 2, -contourThickness * 2));
            contourShape.setPosition(caseShape.getPosition() + sf::Vector2f(contourThickness, contourThickness));
            contourShape.setFillColor(sf::Color::Transparent);
            contourShape.setOutlineThickness(contourThickness);
            contourShape.setOutlineColor(couleurContour);

            // Dessiner le contour
            window.draw(contourShape);

            // Dessiner le point au centre de la case
            sf::CircleShape point(2.0f);
            point.setFillColor(couleurPoint);
            point.setPosition(positions[i] + sf::Vector2f(caseShape.getSize().x / 2.0f, caseShape.getSize().y / 2.0f));
            window.draw(point);
        }

        // Afficher le contenu
        window.display();
    }

    return 0;
}
