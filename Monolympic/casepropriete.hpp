
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#include "joueur.hpp"
#pragma once
#include <vector>
// Classe dérivée pour les cases propriété
class CasePropriete : public Case {
public:
    CasePropriete(int _position, int _cout, bool _estAchete) : Case(_position), cout(_cout), estAchete(_estAchete) {}

    // Méthode pour get l'état de la case
    bool getEtat() const {
        return estAchete;
    }

    // Méthode pour get le cout de la case
    int getCout() const {
        return cout;
    }

    // Méthode pour set l'état de la case
    void setEtat(bool _estAchete) const {
        estAchete = _estAchete;
    }
    // Méthode pour effectuer l'action de la case à une position donnée
void action(Joueur& J, sf::RenderWindow& window) const override {
    if (J.getPoints() >= cout && !estAchete) {
        // Affichage d'un message au milieu avec fond
        sf::Font font;
        if (!font.loadFromFile("police1.otf")) {
            std::cerr << "Erreur lors du chargement de la police" << std::endl;
        }


        //Bouton acheter et annuler
        // Chargement de l'image "acheter.png"
       sf::Texture acheterTexture;
        if (!acheterTexture.loadFromFile("assets/acheter.png")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image acheter" << std::endl;
        }
        sf::Sprite acheterSprite;
        acheterSprite.setTexture(acheterTexture);
        acheterSprite.setOrigin(acheterSprite.getLocalBounds().width / 2.0f, acheterSprite.getLocalBounds().height / 2.0f);
        acheterSprite.setPosition(560, 453);  // Position spécifiée pour "acheterSprite"

        // Chargement de l'image "annuler.png"
        sf::Texture annulerTexture;
        if (!annulerTexture.loadFromFile("assets/annuler.png")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image annuler" << std::endl;
        }
        sf::Sprite annulerSprite;
        annulerSprite.setTexture(annulerTexture);
        annulerSprite.setOrigin(annulerSprite.getLocalBounds().width / 2.0f, annulerSprite.getLocalBounds().height / 2.0f);
        annulerSprite.setPosition(670, 453);  // Position spécifiée pour "annulerSprite"


        sf::Texture modalTexture;
        if (!modalTexture.loadFromFile("assets/modalproprietenew.png")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image modale" << std::endl;
        }
        
        sf::Sprite modalSprite;
        modalSprite.setTexture(modalTexture);
        modalSprite.setPosition(450, 160);  // Position spécifiée

        // Affichage du texte à la position spécifiée
        sf::Text coutText;
        coutText.setFont(font);
        coutText.setString(std::to_string(cout));
        coutText.setCharacterSize(10);
        coutText.setFillColor(sf::Color::Black);
        coutText.setPosition(645, 403);  // Position spécifiée


        // Affichage
        window.draw(modalSprite);
        window.draw(coutText);
        window.draw(annulerSprite); 
        window.draw(acheterSprite);  
        window.display();


        // Boucle pour attendre la réponse du joueur
       // Boucle pour attendre la réponse du joueur
bool reponse = false;
while (!reponse) {
    sf::Event event;
    while (window.pollEvent(event)) {
        // Si on appuie sur la croix rouge
        if (event.type == sf::Event::Closed) {
            window.close();
            return;  // Sortir de la fonction
        }
        // Si on clique sur le cercle vert
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (acheterSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    reponse = true;
                    J.setPoints(J.getPoints() - cout);
                    // dire que l'état de la case à la position est acheté
                    setEtat(true);
                    // ajouter la position de la case à la liste des cases achetées par le joueur
                    std::vector<int> casesAchetees = J.getCasesAchetees();
                            casesAchetees.push_back(getPosition());
                            J.setCasesAchetees(casesAchetees);
                            
                    // Affichage au milieu de la carte de la propriété png
                    sf::Texture texture;
                    if (!texture.loadFromFile("assets/ppt/p" + std::to_string(getPosition()) + ".png")) {
                        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
                    }
                    sf::Sprite sprite;
                    sprite.setTexture(texture);
                    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
                    sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
                    window.draw(sprite);
                    window.display();
                    sf::sleep(sf::seconds(2));
                }
            }
        }
        // Si on clique sur la croix rouge
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (annulerSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    reponse = false;
                    return;  // Sortir de la fonction
                }
            }
        }
    }
}

    }
}

private:
    int cout;
     mutable bool estAchete;
};