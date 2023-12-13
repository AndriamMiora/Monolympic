#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

int main(){



// Pour créer une fenêtre de jeu
    sf::RenderWindow window(sf::VideoMode(1280, 720),
    "by Andrianarivo Ashley & Andriambolo-nivo Miora",
    sf::Style::Close | sf::Style::Titlebar); // Style de la fenêtre : Close = bouton fermer, Titlebar = barre de titre

// Pour charger une police de caractère
    sf::Font stdFont;
    stdFont.loadFromFile("police1.otf");

// Pour charger une image
    sf::Image favicon;
    favicon.loadFromFile("assets/favicon.png");
    window.setIcon(314, 229, favicon.getPixelsPtr()); // 314x229 est la taille de l'image favicon.png

// Pour charger une image de fond
    sf::RectangleShape introScreen(sf::Vector2f(1280.0f, 720.0f));
    sf::Texture introScreenTexture;
    introScreenTexture.loadFromFile("font.jpeg");
    introScreen.setTexture(&introScreenTexture);


// Pour afficher du texte
    sf::Text introScreenText;
    introScreenText.setFont(stdFont);
    introScreenText.setCharacterSize(50);
    introScreenText.setPosition(sf::Vector2f(50.0f, 600.0f));
    // Position du texte en bas à gauche de la fenêtre
    introScreenText.setFillColor(sf::Color::White);
    introScreenText.setString("MONOLYMPIC GAMES");

// Pour afficher du texte
    sf::Text introScreenText2;
    introScreenText2.setFont(stdFont);
    introScreenText2.setCharacterSize(20);
    introScreenText2.setPosition(sf::Vector2f(10.0f, 10.0f));
    introScreenText2.setFillColor(sf::Color::Black);
    introScreenText2.setString("by Andrianarivo Ashley & Andriambolo-nivo Miora\n");

// créer un bouton pour commencer le jeu
    sf::Texture newGameButtonTexture;
    newGameButtonTexture.loadFromFile("assets/new-game-button.png");
    sf::RectangleShape newGameButton(sf::Vector2f(316.0f, 94.0f));
    newGameButton.setTexture(&newGameButtonTexture);
    newGameButton.setPosition(sf::Vector2f(480.0f, 210.0f));

    bool gameStarted = false;

   while (!gameStarted) {
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
            if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (newGameButton.getGlobalBounds().contains(mousePos)) {
                    gameStarted = true;
                }
            }
        }

        window.clear();
        window.draw(introScreen);
        window.draw(introScreenText2);
        window.draw(introScreenText);
        window.draw(newGameButton);
        window.display();
    }



    // Pour charger une image de fond
    sf::Texture selectionScreenTexture;
    selectionScreenTexture.loadFromFile("assets/selection-screen.png");
    sf::RectangleShape selectionScreen(sf::Vector2f(1280.0f, 720.0f));
    selectionScreen.setTexture(&selectionScreenTexture);

    // créer un bouton pour entrer le nom du joueur
    sf::Texture enternametexture;
    enternametexture.loadFromFile("Entername.png");
    sf::RectangleShape enternamebutton(sf::Vector2f(316.0f, 94.0f));
    enternamebutton.setTexture(&enternametexture);
    enternamebutton.setPosition(sf::Vector2f(480.0f, 210.0f));
 
    // Name input box
    sf::RectangleShape nameInputBox(sf::Vector2f(300.0f, 50.0f));
    nameInputBox.setFillColor(sf::Color::White);
    nameInputBox.setPosition(sf::Vector2f(500.0f, 400.0f));

    // Name input text
    sf::Text nameInputText;
    nameInputText.setFont(stdFont);
    nameInputText.setCharacterSize(20);
    nameInputText.setPosition(sf::Vector2f(510.0f, 410.0f));
    nameInputText.setFillColor(sf::Color::Black); // Définir la couleur du texte en noir

    // Ajout bouton pour valider le nom du joueur
    sf::Texture validatetexture;
    validatetexture.loadFromFile("Validate.png");
    sf::RectangleShape validatebutton(sf::Vector2f(316.0f, 94.0f));
    validatebutton.setTexture(&validatetexture);
    validatebutton.setPosition(sf::Vector2f(480.0f, 210.0f));
    

    // Keeps the choice that the user has made.
    // 1 --> New Game

    int choice = -1;


    while (window.isOpen() && gameStarted && choice == -1) {
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::FloatRect enternamebuttonBounds = enternamebutton.getGlobalBounds();
                if (enternamebuttonBounds.contains(mousePos)) {
                    choice = 1;
                    bool nameEntered = false;
                    sf::String playerName;

                    while (!nameEntered && window.isOpen()) {
                        sf::Event nameEvent;
                        while (window.pollEvent(nameEvent)) {
                            if (nameEvent.type == nameEvent.Closed) {
                                window.close();
                            }
                            else if (nameEvent.type == sf::Event::TextEntered) {
                                if (nameEvent.text.unicode < 128) {
                                    if (nameEvent.text.unicode == 8) { // Backspace
                                        if (!playerName.isEmpty()) {
                                            playerName.erase(playerName.getSize() - 1, 1);
                                        }
                                    }
                                    else if (nameEvent.text.unicode == 13) { // Enter
                                        if (!playerName.isEmpty()) {
                                            nameEntered = true;
                                        }
                                    }
                                    else {
                                        playerName += nameEvent.text.unicode;
                                    }
                                }
                            }
                        }

                        // Affiche le nom du joueur en cours de saisie
                        nameInputText.setString(playerName);

                        window.clear();
                        window.draw(selectionScreen);
                        window.draw(enternamebutton);
                        window.draw(nameInputBox);
                        window.draw(nameInputText);
                        window.display();
                    }

                }

            }

        }
        window.clear();
        window.draw(selectionScreen);
        window.draw(enternamebutton);
        window.display();
    }

    window.close();
    return 0;
}



