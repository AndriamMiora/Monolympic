#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

int main(){
// Creating an SFML window
    sf::RenderWindow window(sf::VideoMode(1280, 720),
        "by Andrianarivo Ashley & Andriambolo-nivo Miora",
        sf::Style::Close | sf::Style::Titlebar);

    // Standard Font
    sf::Font stdFont;
    stdFont.loadFromFile("fonts/Montserrat-Black.ttf");


    // Implementing the favicon
    sf::Image favicon;
    favicon.loadFromFile("assets/favicon.png");
    window.setIcon(314, 229, favicon.getPixelsPtr());

    // Intro screen
    sf::RectangleShape introScreen(sf::Vector2f(1280.0f, 720.0f));
    sf::Texture introScreenTexture;
    introScreenTexture.loadFromFile("font.jpeg");
    introScreen.setTexture(&introScreenTexture);

    sf::Font montLight;
    montLight.loadFromFile("fonts/Montserrat-Light.ttf");

    sf::Text introScreenText[3];
    for (int i = 0; i < 3; i++) {
    
        introScreenText[i].setFont(montLight);
        introScreenText[i].setString((i == 0) ? "START GAME" : "EXIT GAME");
        introScreenText[i].setCharacterSize(22);

    }

    introScreenText[2].setString("MONOLYMPIC GAMES");
    introScreenText[2].setCharacterSize(15);

    introScreenText[0].setPosition(570.0f, 450.0f);
    introScreenText[1].setPosition(580.0f, 520.0f);
    introScreenText[2].setPosition(370.0f, 690.0f);

    bool gameStarted = false;

    while (!gameStarted) {

        sf::Event evt;
        while (window.pollEvent(evt)) {
        
            if (evt.type == evt.Closed) {
            
                window.close();

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::FloatRect startGameBounds = introScreenText[0].getGlobalBounds();
                sf::FloatRect exitBounds = introScreenText[1].getGlobalBounds();


                if (exitBounds.contains(mousePos)) {

                    window.close();

                }

                if (startGameBounds.contains(mousePos)) {
                
                    gameStarted = true;

                }

            }

        }

        window.clear();
        window.draw(introScreen);
        
        window.draw(introScreenText[0]);
        window.draw(introScreenText[2]);


        window.display();

    }

    // Selection screen to get the user choice
    // for either new game or load game

    // Creating in-game assets for screen rendering

    sf::Texture selectionScreenTexture;
    selectionScreenTexture.loadFromFile("assets/selection-screen.png");
    sf::RectangleShape selectionScreen(sf::Vector2f(1280.0f, 720.0f));
    selectionScreen.setTexture(&selectionScreenTexture);

    // New game button
    sf::Texture newGameButtonTexture;
    newGameButtonTexture.loadFromFile("assets/new-game-button.png");
    sf::RectangleShape newGameButton(sf::Vector2f(316.0f, 94.0f));
    newGameButton.setTexture(&newGameButtonTexture);

    newGameButton.setPosition(sf::Vector2f(480.0f, 210.0f));

    // Enter a name text
    sf::Text enterNameText;
    enterNameText.setFont(stdFont);
    enterNameText.setString("ENTER YOUR NAME");
    enterNameText.setCharacterSize(20);
    enterNameText.setPosition(sf::Vector2f(500.0f, 350.0f));

    // Name input box
    sf::RectangleShape nameInputBox(sf::Vector2f(300.0f, 50.0f));
    nameInputBox.setFillColor(sf::Color::White);
    nameInputBox.setPosition(sf::Vector2f(500.0f, 400.0f));


    // Name input text
    sf::Text nameInputText;
    nameInputText.setFont(stdFont);
    nameInputText.setCharacterSize(20);
    nameInputText.setPosition(sf::Vector2f(510.0f, 410.0f));


    // Keeps the choice that the user has made.
    // 1 --> New Game

    int choice = -1;


    while (window.isOpen() && gameStarted && choice == -1) {

        sf::Event evt;
        while (window.pollEvent(evt)) {


            if (evt.type == evt.Closed) {

                window.close();

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                sf::FloatRect newGameButtonBounds = newGameButton.getGlobalBounds();
              

                if (newGameButtonBounds.contains(mousePos)) {

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
                        window.draw(newGameButton);
                        window.draw(enterNameText);
                        window.draw(nameInputBox);
                        window.draw(nameInputText);
                        window.display();
                    }
                    
            

                }

            


            }

            window.draw(selectionScreen);
            window.draw(newGameButton);
    
            window.display();

        }

    }

    gameStarted = false;

    while (!gameStarted) {

        if (choice == 1) {

            gameStarted = true;

            // Keeps the total number of players
            // that the user has asked for
            // the game supports 3 - 5 players.
            int totalPlayers = -1;

            // Background screen
            sf::Texture playerNumberScreenTexture;
            //playerNumberScreenTexture.loadFromFile("assets/player-number-selection-screen.png");
            playerNumberScreenTexture.loadFromFile("assets/selection-screen.png");
            sf::RectangleShape playerNumberScreen(sf::Vector2f(1280.0f, 720.0f));
            playerNumberScreen.setTexture(&playerNumberScreenTexture);


            // Card that shows 3 players
            sf::Texture threePlayerTexture;
            threePlayerTexture.loadFromFile("assets/3-player-card.png");
            sf::RectangleShape threePlayerCard(sf::Vector2f(251.0f, 272.0f));
            threePlayerCard.setTexture(&threePlayerTexture);
            threePlayerCard.setPosition(sf::Vector2f(250.0f, 200.0f));

            // Card that shows 4 players
            sf::Texture fourPlayerTexture;
            fourPlayerTexture.loadFromFile("assets/4-player-card.png");
            sf::RectangleShape fourPlayerCard(sf::Vector2f(251.0f, 272.0f));
            fourPlayerCard.setTexture(&fourPlayerTexture);
            fourPlayerCard.setPosition(sf::Vector2f(
                threePlayerCard.getPosition().x + 260, threePlayerCard.getPosition().y));

            // Card that shows 5 players
            sf::Texture fivePlayerTexture;
            fivePlayerTexture.loadFromFile("assets/5-player-card.png");
            sf::RectangleShape fivePlayerCard(sf::Vector2f(251.0f, 272.0f));
            fivePlayerCard.setTexture(&fivePlayerTexture);
            fivePlayerCard.setPosition(sf::Vector2f(
                fourPlayerCard.getPosition().x + 260, threePlayerCard.getPosition().y));

            bool playerSelected = false;

            sf::Clock clk;

            while (!playerSelected) {


                sf::Event evt;
                while (window.pollEvent(evt)) {


                    if (evt.type == evt.Closed) {

                        window.close();

                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        // Checks if any of the cards have been clicked

                        sf::FloatRect threeCardBound = threePlayerCard.getGlobalBounds();
                        sf::FloatRect fourCardBound = fourPlayerCard.getGlobalBounds();
                        sf::FloatRect fiveCardBound = fivePlayerCard.getGlobalBounds();

                        if (threeCardBound.contains(mousePos)) totalPlayers = 3;
                        if (fourCardBound.contains(mousePos)) totalPlayers = 4;
                        if (fiveCardBound.contains(mousePos)) totalPlayers = 5;


                    }

                }

                if (totalPlayers == -1)
                    clk.restart();


                if (totalPlayers != -1 && clk.getElapsedTime().asMilliseconds() < 1200) {


                    threePlayerCard.setPosition(threePlayerCard.getPosition().x, threePlayerCard.getPosition().y - (clk.getElapsedTime().asSeconds() * 12.0f));

                    fourPlayerCard.setPosition(fourPlayerCard.getPosition().x, fourPlayerCard.getPosition().y - (clk.getElapsedTime().asSeconds() * 10.0f));

                    fivePlayerCard.setPosition(fivePlayerCard.getPosition().x, fivePlayerCard.getPosition().y - (clk.getElapsedTime().asSeconds() * 8.0f));


                }

                if (totalPlayers != -1 && clk.getElapsedTime().asMilliseconds() > 1200) {

                    clk.restart();
                    playerSelected = true;

                }


                window.draw(playerNumberScreen);
                window.draw(threePlayerCard);
                window.draw(fourPlayerCard);
                window.draw(fivePlayerCard);
                window.display();

            }



        }
        else {

            window.clear();
            window.draw(selectionScreen);
            window.display();
        
        }


window.close();

    }

return 0;

}
