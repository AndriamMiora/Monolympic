#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <vector>
#include "case.hpp"
#include "Pion.hpp"
#include "Des.hpp"
#include "Button.hpp"
#include "tableau.hpp"
#include <string>
#include "joueur.hpp"
#include "BotJoueur.hpp"
#include <SFML/System/Clock.hpp>
#include "Affichage.hpp"

using namespace std;

std::tuple<bool, std::string, std::string, sf::Font> setupGame(sf::RenderWindow& window) {
// avant de commencer le jeu 
    Affichage affichage;
    // Pour créer une fenêtre de jeu
    auto result = affichage.setupIntroScreen(window);
    bool gameStarted = std::get<0>(result);
    std::string playerName = std::get<1>(result);

    sf::Font stdFont;
    stdFont.loadFromFile("police1.otf");
    auto selectionScreen = affichage.createSelectionWindow(window, playerName, stdFont, gameStarted);
   
    std::string playerPion = affichage.selectPlayerPion(window);    
    

    return std::make_tuple(gameStarted, playerName, playerPion, stdFont);
}

void drawpion(sf::RenderWindow& window, Joueur* joueur1, Joueur* joueur2, const std::vector<sf::Vector2f>& points, const std::string& playerPion) {
    // Load textures outside the loop
    sf::Texture texture1;
    sf::Texture texture2;

    if (playerPion == "pion1") {
        if (!texture1.loadFromFile("assets/couleur1.png")) {
            std::cout << "Erreur lors du chargement de l'image du dé." << std::endl;
            return;  // Exit the function if loading fails
        }
        if (!texture2.loadFromFile("assets/couleur2.png")) {
            std::cout << "Erreur lors du chargement de l'image du dé." << std::endl;
            return;  // Exit the function if loading fails
        }
    } else if (playerPion == "pion2") {
        if (!texture1.loadFromFile("assets/couleur2.png")) {
            std::cout << "Erreur lors du chargement de l'image du dé." << std::endl;
            return;  // Exit the function if loading fails
        }
        if (!texture2.loadFromFile("assets/couleur1.png")) {
            std::cout << "Erreur lors du chargement de l'image du dé." << std::endl;
            return;  // Exit the function if loading fails
        }
    }

    // Create sprites
    std::vector<sf::Sprite> caseJoueur1(joueur1->getCasesAchetees().size());
    std::vector<sf::Sprite> caseJoueur2(joueur2->getCasesAchetees().size());

    // Define size reduction and horizontal offset
    float sizeReduction = 0.3f;  // You can adjust this value
    float xOffset = 5.0f;  // You can adjust this value

    // Populate sprites
    for (size_t i = 0; i < joueur1->getCasesAchetees().size(); ++i) {
        caseJoueur1[i].setTexture(texture1);
        caseJoueur1[i].setPosition(points[joueur1->getCasesAchetees()[i]]);
        caseJoueur1[i].setScale(sizeReduction, sizeReduction);  // Apply size reduction
        caseJoueur1[i].move(xOffset, 0.0f);  // Move to the right
    }

    for (size_t i = 0; i < joueur2->getCasesAchetees().size(); ++i) {
        caseJoueur2[i].setTexture(texture2);
        caseJoueur2[i].setPosition(points[joueur2->getCasesAchetees()[i]]);
        caseJoueur2[i].setScale(sizeReduction, sizeReduction);  // Apply size reduction
        caseJoueur2[i].move(xOffset, 0.0f);  // Move to the right
    }

    // Draw sprites
    for (const auto& sprite : caseJoueur1) {
        window.draw(sprite);
    }

    for (const auto& sprite : caseJoueur2) {
        window.draw(sprite);
    }

    window.display();
}





void drawGameElements(sf::RenderWindow& window, Button& rollButton, sf::Sprite& sprite, Joueur* joueur1, Joueur* joueur2, std::vector<sf::Sprite>& diceSprites, sf::Text& joueur1PointsText, sf::Text& joueur2PointsText, sf::Text& playerNameText, sf::Sprite& tourSprite, sf::Text& timeText, std::vector<sf::Vector2f>& points, std::string playerPion) {
    window.draw(sprite);
    for (size_t i = 0; i < diceSprites.size(); ++i) {
        window.draw(diceSprites[i]);
    }
    joueur1PointsText.setString(std::to_string(joueur1->getPoints()));
    joueur2PointsText.setString(std::to_string(joueur2->getPoints()));

    window.draw(joueur1PointsText);
    window.draw(joueur2PointsText);
    window.draw(playerNameText);
    joueur1->getPion()->afficher(window);
    joueur2->getPion()->afficher(window);
    rollButton.draw(window); 
    window.draw(timeText);
    drawpion(window, joueur1, joueur2, points, playerPion);
    window.display();
}


// début du jeu
void beginGame() {
    Affichage affichage;
    sf::RenderWindow window(sf::VideoMode(1280, 720),
    "by Andrianarivo Ashley & Andriambolo-nivo Miora",
    sf::Style::Close | sf::Style::Titlebar); // Style de la fenêtre : Close = bouton fermer, Titlebar = barre de titre
    auto result = setupGame(window);
    bool gameStarted = std::get<0>(result);
    std::string playerName = std::get<1>(result);
    std::string playerPion = std::get<2>(result);
    sf::Font stdFont = std::get<3>(result);
    
    Tableau tableau;
    std::vector<sf::Vector2f> points = tableau.getPoints();

    Des des;
    int position1 = 0;
    int position2 = 0;

    // Création des joueurs
    Joueur* joueur1 = new Joueur(/* ... */);
    Joueur* joueur2 = new Joueur(/* ... */);
    joueur2->setBot(true);

    // Création des textes pour afficher les points de chaque joueur
    sf::Text joueur1PointsText;
    joueur1PointsText = affichage.createAndInitializeText(stdFont, 14, sf::Color::Black, sf::Vector2f(1084, 554), std::to_string(joueur1->getPoints()));
    sf::Text joueur2PointsText;
    joueur2PointsText = affichage.createAndInitializeText(stdFont, 14, sf::Color::Black, sf::Vector2f(100, 508) , std::to_string(joueur2->getPoints()));
    // Affichage du nom du joueur 
    sf::Text playerNameText;
    playerNameText = affichage.createAndInitializeText(stdFont, 24, sf::Color::Black, sf::Vector2f(1110, 279), playerName);

    sf::Texture tour;
    tour.loadFromFile("assets/tour.jpg");
    sf::Sprite tourSprite;
    tourSprite.setTexture(tour);
    tourSprite.setOrigin(tour.getSize().x / 2.0f, tour.getSize().y / 2.0f);
    tourSprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    tourSprite.setScale(1.0f, 1.0f);
   
    // Initialisation du pion du joueur en bas à droite du plateau
    Pion pion("assets/pion.png",  sf::Vector2f(871.900024, 624.000000), 0);
    Pion pion2("assets/pion.png",  sf::Vector2f(881.900024, 624.000000), 0);
    if (playerPion == "pion1") {
        pion.setCheminImage("assets/pion.png");
        joueur1->setPion(&pion);

        pion2.setCheminImage("assets/pion2.png");
        joueur2->setPion(&pion2);
        tableau.addJoueur(joueur2);
        
    } else if (playerPion == "pion2") {
        pion.setCheminImage("assets/pion2.png");
        joueur1->setPion(&pion);
        tableau.addJoueur(joueur1);

        pion2.setCheminImage("assets/pion.png");
        joueur2->setPion(&pion2);
        tableau.addJoueur(joueur2);
    } 
    sf::Texture texture;
    std::string boardImage = "assets/board1.png";  // Image par défaut pour le pion1
    if (playerPion == "pion2") {
        boardImage = "assets/board2.png";
    }
    texture.loadFromFile(boardImage);
    sf::Sprite sprite = sf::Sprite(texture);

    Button rollButton("assets/roll.png");
    float xPosition = rollButton.createRollButton("assets/roll.png", window).first;
    float yPosition = rollButton.createRollButton("assets/roll.png", window).second;
    rollButton.setPosition(sf::Vector2f(xPosition, yPosition));
    rollButton.setScale(sf::Vector2f(0.2f, 0.2f));  // Ajustement de la taille

    std::vector<sf::Sprite> diceSprites;

    bool joueur1Turn = true;

    sf::Clock globalTimer;  // Horloge globale pour suivre le temps total écoulé
    const sf::Time timeLimit = sf::seconds(600.0f);  // Limite de temps pour le jeu
    sf::Text timeText = affichage.createAndInitializeTimeText(stdFont);



   while (window.isOpen() && globalTimer.getElapsedTime() < timeLimit) {
    sf::Time elapsed = globalTimer.getElapsedTime();
    sf::Event event;
    joueur1PointsText.setString(std::to_string(joueur1->getPoints()));
    joueur2PointsText.setString(std::to_string(joueur2->getPoints()));

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // Seul le joueur humain peut cliquer sur le bouton
        if (joueur1Turn && !rollButton.isClicked()) {
            rollButton.handleEvent(event, window);
        }
        if (joueur1Turn && rollButton.isClicked()) {
            // Lancer les dés et obtenir les résultats
            auto result1 = tableau.initializeDiceSprites(des, rollButton.getPosition(), position1, points, joueur1, window);
            diceSprites = result1.first;
            position1 = result1.second;

            window.clear();
            drawGameElements(window, rollButton, sprite, joueur1, joueur2, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, points, playerPion);
            rollButton.draw(window);
            window.display();
            // Attendre un court moment pour afficher les dés avant de réaliser l'action
            sf::sleep(sf::milliseconds(1000));  // Ajoutez le temps souhaité en millisecondes

            // Réaliser l'action après l'affichage des dés
            tableau.actionAtPosition(position1, window, points, joueur1);
            window.clear();
            drawGameElements(window, rollButton, sprite, joueur1, joueur2, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, points, playerPion);
            rollButton.draw(window);
            window.display();
            rollButton.resetClicked();
        
            // Changer de joueur
            joueur1Turn = false;

            sf::sleep(sf::seconds(3));
        } else if (!joueur1Turn) {
            int currentPos = joueur2->getPion()->getPos();
            auto result2 = tableau.initializeDiceSprites(des, rollButton.getPosition(), currentPos, points, joueur2, window);
            diceSprites = result2.first;
            joueur2->getPion()->setPos(result2.second);
            position2 = result2.second;
            window.clear();
            drawGameElements(window, rollButton, sprite, joueur1, joueur2, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, points, playerPion);
            rollButton.draw(window);
            window.display();
            // Attendre un court moment pour afficher les dés avant de réaliser l'action
            sf::sleep(sf:: milliseconds(1000));  // Ajoutez le temps souhaité en millisecondes
            // Réaliser l'action après l'affichage des dés
            tableau.actionAtPosition(position2, window, points, joueur2);
            window.clear();
            drawGameElements(window, rollButton, sprite, joueur1, joueur2, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, points, playerPion);
            rollButton.draw(window);
            window.display();
            rollButton.resetClicked();
            joueur1Turn = true;
            window.draw(tourSprite);
            window.display();
            sf::sleep(sf::seconds(2));
        }
    }
 
    drawGameElements(window, rollButton, sprite, joueur1, joueur2, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, points, playerPion);

    // mise à jour du temps
    // Mise à jour du texte du temps écoulé
    sf::Time elapsedTime = globalTimer.getElapsedTime();
    int minutes = static_cast<int>(elapsedTime.asSeconds()) / 60;
    int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;

    timeText.setString("Timer : " + std::to_string(minutes) + " min " + std::to_string(seconds) + " sec");
    // Dessinez les éléments du jeu
    window.draw(timeText);

    window.display();

}
}












    


