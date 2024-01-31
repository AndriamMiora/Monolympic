#pragma once 
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
#include <SFML/System/Clock.hpp>
#include "Affichage.hpp"
#include <SFML/Audio.hpp>
using namespace std;

class Jeu {
public:

    Jeu() {}
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
        sf::Texture texture1, texture2; // Load textures outside the loop
        if (playerPion == "pion1") {
            texture1.loadFromFile("assets/couleur1.png");
            texture2.loadFromFile("assets/couleur2.png");
        } else if (playerPion == "pion2") {
            texture1.loadFromFile("assets/couleur2.png");
            texture2.loadFromFile("assets/couleur1.png");   
        }
        // Create sprites
        std::vector<sf::Sprite> caseJoueur1(joueur1->getCasesAchetees().size()), caseJoueur2(joueur2->getCasesAchetees().size());
        for (size_t i = 0; i < joueur1->getCasesAchetees().size(); ++i) {
            caseJoueur1[i].setTexture(texture1);
            caseJoueur1[i].setPosition(points[joueur1->getCasesAchetees()[i]]);
            caseJoueur1[i].setScale(0.3f, 0.3f);  // Apply size reduction
            caseJoueur1[i].move(5.0f, 0.0f);  // Move to the right
        }
        for (size_t i = 0; i < joueur2->getCasesAchetees().size(); ++i) {
            caseJoueur2[i].setTexture(texture2);
            caseJoueur2[i].setPosition(points[joueur2->getCasesAchetees()[i]]);
            caseJoueur2[i].setScale(0.3f, 0.3f);  // Apply size reduction
            caseJoueur2[i].move(5.0f, 0.0f);  // Move to the right
        }
        for (const auto& sprite : caseJoueur1) {    // Draw sprites
            window.draw(sprite);
        }
        for (const auto& sprite : caseJoueur2) {   // Draw sprites
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
    void initializePionAndPlayer(Joueur* joueur, Pion& pion, const std::string& imagePath, float posX, float posY) {
        pion.setCheminImage(imagePath);
        joueur->setPion(&pion);
    }

    void initializePionAndPlayers(const std::string& playerPion, Joueur* joueur1, Joueur* joueur2, Pion& pion1, Pion& pion2, Tableau& tableau) {
        if (playerPion == "pion1") {
            initializePionAndPlayer(joueur1, pion1, "assets/pion.png", 871.9f, 624.0f);
            initializePionAndPlayer(joueur2, pion2, "assets/pion2.png", 881.9f, 624.0f);
        } else if (playerPion == "pion2") {
            initializePionAndPlayer(joueur1, pion1, "assets/pion2.png", 871.9f, 624.0f);
            initializePionAndPlayer(joueur2, pion2, "assets/pion.png", 881.9f, 624.0f);
        }
        tableau.addJoueur(joueur1);
        tableau.addJoueur(joueur2);
    }

    void setupTimeText(sf::Text& timeText, const sf::Font& stdFont) {
        timeText.setFont(stdFont);
        timeText.setCharacterSize(24);
        timeText.setFillColor(sf::Color::White);
        timeText.setPosition(10.f, 10.f);  // Ajustez la position selon vos besoins
    }


    void performTurn(Joueur* joueur, int& position, std::vector<sf::Vector2f>& points, sf::RenderWindow& window, Tableau& tableau, Button& rollButton, sf::Sprite& sprite, std::vector<sf::Sprite>& diceSprites, sf::Text& joueur1PointsText, sf::Text& joueur2PointsText, sf::Text& playerNameText, sf::Sprite& tourSprite, sf::Text& timeText, const std::string& playerPion, Des& des, Joueur* joueur1, Joueur* joueur2) {
        window.clear();
        auto result = tableau.initializeDiceSprites(des, rollButton.getPosition(), position, points, joueur, window);
        diceSprites = result.first;
        position = result.second;
        joueur->getPion()->setPos(result.second);
        joueur->getPion()->setPosition(points[result.second]);
        window.clear();
        drawGameElements(window, rollButton, sprite, joueur1, joueur2, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, points, playerPion);
        rollButton.draw(window);
        window.display();
        sf::sleep(sf::milliseconds(1000));
        tableau.actionAtPosition(position, window, points, joueur);
        window.clear();
        drawGameElements(window, rollButton, sprite, joueur1, joueur2, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, points, playerPion);
        rollButton.draw(window);
        window.display();
        rollButton.resetClicked();
    }

    void updateTimerAndDisplay(sf::RenderWindow& window, sf::Clock& globalTimer, sf::Text& timeText) {
        sf::Time elapsedTime = globalTimer.getElapsedTime();
        int minutes = static_cast<int>(elapsedTime.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;
        timeText.setString("Temps restant : " + std::to_string(minutes) + " min " + std::to_string(seconds) + " sec");
        window.draw(timeText);
        window.display();
    }
    void calculeScore(Joueur* joueur, Joueur* joueur2, Tableau& tableau) {
        // caclule le nombre de médailles + couts des ppriétés que chaque joueur a
        int medaillesJoueur1 = joueur->getPoints();
        int medaillesJoueur2 = joueur2->getPoints();
        int coutProprietesJoueur1 = 0;
        int coutProprietesJoueur2 = 0;
        
        // joueur à la liste des positions des propriétés qu'il a
        std::vector<int> positionsJoueur1 = joueur->getCasesAchetees();
        std::vector<int> positionsJoueur2 = joueur2->getCasesAchetees();
        // pour chaque position, on ajoute le cout de la propriété à la somme totale
        for (int i = 0; i < positionsJoueur1.size(); ++i) {
            coutProprietesJoueur1 += tableau.getCaseAtPosition(positionsJoueur1[i])->getCout();
        }
        for (int i = 0; i < positionsJoueur2.size(); ++i) {
            coutProprietesJoueur2 += tableau.getCaseAtPosition(positionsJoueur2[i])->getCout();
        }
        // on calcule le score final de chaque joueur
        int scoreJoueur1 = medaillesJoueur1 + coutProprietesJoueur1;
        int scoreJoueur2 = medaillesJoueur2 + coutProprietesJoueur2;
        joueur->setPoints(scoreJoueur1);
        joueur2->setPoints(scoreJoueur2);
        // affciher le score final de chaque joueur dans le terminal
        std::cout << "Score final du joueur 1 : " << scoreJoueur1 << std::endl;
        std::cout << "Score final du joueur 2 : " << scoreJoueur2 << std::endl;

    }
    void endGame(sf::RenderWindow& window, Joueur* joueur1, Joueur* joueur2, Tableau& tableau) {
        sf::Texture fondTexture; Affichage affichage;
        fondTexture.loadFromFile("assets/background.png");
        // Créer le sprite pour le fond
        sf::Sprite fondSprite;
        fondSprite.setTexture(fondTexture);
        fondSprite.setScale(1.0f, 1.0f);
        window.draw(fondSprite);
        calculeScore(joueur1, joueur2, tableau);
        sf::Texture texture;
       if (*joueur1 == *joueur2) { // utiliser l'opérateur == surchargé
        texture.loadFromFile("assets/egalite.jpg");
        std::cout << "Égalité !" << std::endl;
    } else {
        if (*joueur1 < *joueur2) {
            texture.loadFromFile("assets/perdant.jpg");
            std::cout << "Le joueur 1 a perdu." << std::endl;
        } else {
            texture.loadFromFile("assets/gagnant.jpg");
            std::cout << "Le joueur 1 a gagné." << std::endl;
        }
    }
        sf::Sprite Sprite;
        Sprite.setTexture(texture);
        affichage.Drawgagner(window, Sprite);
        window.display();
        sf::sleep(sf::seconds(5));
    }

    int comptetour(Joueur* joueur, int tour) {
        int tourne = tour;
        if (joueur->getFermerVille() == true) {
                        if (tourne== 2){
                            joueur->setFermerVille(false);
                            tourne= 0;
                        }
                        else {
                            tour++;
                        }
                    }
        return tourne; 
    }

    void runGameLoop(sf::RenderWindow& window, Joueur* joueur1, Joueur* joueur2, std::vector<sf::Vector2f>& points, Des& des, Button& rollButton, sf::Sprite& sprite, std::vector<sf::Sprite>& diceSprites, sf::Text& joueur1PointsText, sf::Text& joueur2PointsText, sf::Text& playerNameText, sf::Sprite& tourSprite, sf::Text& timeText, bool& joueur1Turn, sf::Clock& globalTimer, const sf::Time& timeLimit, const std::string& playerPion, Tableau& tableau) {
        int position1 = 0, position2 = 0;
        int tourjoueur = 0; int tourbot = 0;
        while (window.isOpen() && globalTimer.getElapsedTime() < timeLimit) {
            sf::Time elapsed = globalTimer.getElapsedTime(); sf::Event event;
            joueur1PointsText.setString(std::to_string(joueur1->getPoints()));
            joueur2PointsText.setString(std::to_string(joueur2->getPoints()));
            while (window.pollEvent(event)) {
                tourjoueur = comptetour(joueur1, tourjoueur); tourbot = comptetour(joueur2, tourbot);
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (joueur1Turn && !rollButton.isClicked()) {
                    rollButton.handleEvent(event, window);
                }
                if (joueur1Turn && rollButton.isClicked() && joueur1->getFermerVille() == false) {
                    performTurn(joueur1, position1, points, window, tableau, rollButton, sprite, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, playerPion, des, joueur1, joueur2);
                    updateTimerAndDisplay(window, globalTimer, timeText);
                    joueur1Turn = false;
                    sf::sleep(sf::seconds(3));
                } else if (!joueur1Turn && joueur2->getFermerVille() == false) {
                    performTurn(joueur2, position2, points, window, tableau, rollButton, sprite, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, playerPion, des, joueur1, joueur2);
                    updateTimerAndDisplay(window, globalTimer, timeText);
                    joueur1Turn = true;
                    window.draw(tourSprite); window.display();
                    sf::sleep(sf::seconds(2));
                }
            }
            window.clear();
            drawGameElements(window, rollButton, sprite, joueur1, joueur2, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, points, playerPion);
            updateTimerAndDisplay(window, globalTimer, timeText);       
        }  
    }



    void beginGame() {
        sf::Music backgroundMusic;
        backgroundMusic.openFromFile("assets/monopoly.mp3");
        backgroundMusic.setVolume(50);
        backgroundMusic.setLoop(true);
        backgroundMusic.play();
        Affichage affichage;
        sf::RenderWindow window(sf::VideoMode(1280, 720), "by Andrianarivo Ashley & Andriambolo-nivo Miora", sf::Style::Close | sf::Style::Titlebar);
        auto [gameStarted, playerName, playerPion, stdFont] = setupGame(window);
        Tableau tableau; std::vector<sf::Vector2f> points = tableau.getPoints();
        Des des;
        Joueur *joueur1 = new Joueur(/* ... */), *joueur2 = new Joueur(/* ... */); joueur2->setBot(true);
        sf::Text joueur1PointsText, joueur2PointsText, playerNameText;
        joueur1PointsText = affichage.createAndInitializeText(stdFont, 14, sf::Color::Black, sf::Vector2f(1084, 554), std::to_string(joueur1->getPoints()));
        joueur2PointsText = affichage.createAndInitializeText(stdFont, 14, sf::Color::Black, sf::Vector2f(100, 508), std::to_string(joueur2->getPoints()));
        playerNameText = affichage.createAndInitializeText(stdFont, 24, sf::Color::Black, sf::Vector2f(1110, 279), playerName);
        sf::Texture tour; tour.loadFromFile("assets/tour.jpg"); sf::Sprite tourSprite(tour);
        tourSprite.setOrigin(tour.getSize().x / 2.0f, tour.getSize().y / 2.0f);
        tourSprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        tourSprite.setScale(1.0f, 1.0f);
        Pion pion1("assets/pion.png", sf::Vector2f(871.9f, 624.0f), 0), pion2("assets/pion.png", sf::Vector2f(881.9f, 624.0f), 0);
        initializePionAndPlayers(playerPion, joueur1, joueur2, pion1, pion2, tableau);
        sf::Texture texture;
        texture.loadFromFile((playerPion == "pion2") ? "assets/board2.png" : "assets/board1.png");
        sf::Sprite sprite(texture);
        Button rollButton("assets/roll.png");
        float xPosition = rollButton.createRollButton("assets/roll.png", window).first;
        float yPosition = rollButton.createRollButton("assets/roll.png", window).second;
        rollButton.setPosition(sf::Vector2f(xPosition, yPosition));
        rollButton.setScale(sf::Vector2f(0.2f, 0.2f));  // Ajustement de la taille
        std::vector<sf::Sprite> diceSprites;
        bool joueur1Turn = true;
        sf::Clock globalTimer; const sf::Time timeLimit = sf::seconds(600.0f);
        sf::Text timeText; setupTimeText(timeText, stdFont);
        runGameLoop(window, joueur1, joueur2, points, des, rollButton, sprite, diceSprites, joueur1PointsText, joueur2PointsText, playerNameText, tourSprite, timeText, joueur1Turn, globalTimer, timeLimit, playerPion, tableau);
        endGame(window, joueur1, joueur2, tableau);
    }   
};






    


