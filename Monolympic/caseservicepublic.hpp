#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#pragma once
#include <vector>
#include <string>
#include "joueur.hpp"
#include "casepayante.hpp"
// Classe dérivée pour les cases service public
class CaseServicePublic : public CasePayante {
private : 
    std::string nomService;
public:
    CaseServicePublic(int _position, int _cout, bool _estAchete, std::string _nomService)
        : CasePayante(_position, _cout, _estAchete),
          nomService(_nomService) {} 

    // Méthode pour obtenir le nom du service public
    std::string getNomService() const {
        return nomService;
    }
    void initializeSprite(sf::Sprite& sprite, const sf::Vector2f& position, const sf::Vector2f& scale) const  {
    sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f) ; 
    sprite.setPosition(position);
    sprite.setScale(scale.x, scale.y);
}
    // Méthode pour mettre à jour le nom du service public
    void setNomService(std::string _nomService) {
        nomService = _nomService;
    }

    // Méthode pour obtenir l'état de la case
    bool getEtat() const {
        return estAchete;
    }

    // Méthode pour obtenir le coût de la case
    int getCout() const {
        return cout;
    }
    
    // Méthode pour set l'état de la case
    void setEtat(bool _estAchete) const {
        estAchete = _estAchete;
    }

    // pour mettre en place l'action du bot
    void actionbot(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points , int number1, int number2 ) const {
    if (J.getPoints() >= cout && !estAchete && number1 == 1) {
            J.setPoints(J.getPoints() - cout);
            setEtat(true);
            std::vector<int> casesAchetees = J.getCasesAchetees();
            casesAchetees.push_back(getPosition());
            J.setCasesAchetees(casesAchetees);
            window.display();
            sf::sleep(sf::seconds(2)) ;
    }
    
}

// pour attendre la réponse du joueur
void waitForPlayerResponse(sf::RenderWindow& window, sf::Sprite& acheterSprite, sf::Sprite& annulerSprite, Joueur& J) const {
    if (J.getBot() == true) { 
        int number = rand() % 2 + 1;  // prendre un nombre aléatoire entre 1 et 2 pour choisir si le bot achète ou non
        actionbot(J, window, std::vector<sf::Vector2f>(), number, 0);
        } 
    else{ bool reponse = false; // si n'est pas un bot alors on attend la réponse du joueur
    window.display();
    while (!reponse) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (acheterSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    reponse = true;
                    J.setPoints(J.getPoints() - cout);
                    setEtat(true);
                    std::vector<int> casesAchetees = J.getCasesAchetees();
                    casesAchetees.push_back(getPosition());
                    J.setCasesAchetees(casesAchetees);
                    sf::sleep(sf::seconds(2));
                } else if (annulerSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    reponse = false;
                    window.clear();
                    return;
                }
            }
        }
    }
}
}

// pour trouver si la position de la case est dans la liste des cases achetées par le joueur
 bool findposition(int position, Joueur& J) const { 
    for (int i = 0; i < J.getCasesAchetees().size(); i++) {
        if (J.getCasesAchetees()[i] == position) {
            return true;
        }
    }
    return false;
}

// action de la case service public
void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const {
    int position = J.getPion()->getPos();
    if (estAchete && !(findposition(position, J))) { // si la case est achetée et que le joueur n'est pas le propriétaire
        if (J.getPoints() >= cout) { J.setPoints(J.getPoints() - cout);}  // paie le loyer
        else { J.setPoints (0); } }
    else { if (J.getPoints() >= cout && !estAchete) { // si la case n'est pas achetée et que le joueur a assez de points
            sf::Font font;font.loadFromFile("police1.otf");
            sf::Texture acheterTexture, annulerTexture, modalTexture;
            if (position == 12) {
                acheterTexture.loadFromFile("assets/sp1_acheter.png");modalTexture.loadFromFile("assets/électricité.jpg");
            } else if (position == 35) {
                acheterTexture.loadFromFile("assets/sp2_acheter.png");modalTexture.loadFromFile("assets/personne.jpg");
            } else if (position == 38) {
                acheterTexture.loadFromFile("assets/sp3_acheter.png");modalTexture.loadFromFile("assets/eau.jpg");
            }
            annulerTexture.loadFromFile("assets/annuler.png");
            sf::Sprite acheterSprite, annulerSprite, modalSprite;
            acheterSprite.setTexture(acheterTexture); annulerSprite.setTexture(annulerTexture); modalSprite.setTexture(modalTexture);
            initializeSprite(acheterSprite, sf::Vector2f(560, 453), sf::Vector2f(0.5, 0.5));
            initializeSprite(annulerSprite, sf::Vector2f(670, 453), sf::Vector2f(1.0, 1.0));
            modalSprite.setTexture(modalTexture);
            modalSprite.setPosition(450, 160);  modalSprite.setScale(0.62, 0.62);
            sf::Text coutText; coutText.setFont(font);coutText.setCharacterSize(10);
            coutText.setFillColor(sf::Color::Black);coutText.setPosition(645, 403);  // Position spécifiée
            window.draw(modalSprite);
            window.draw(coutText);
            window.draw(annulerSprite);
            window.draw(acheterSprite);
            waitForPlayerResponse(window, acheterSprite, annulerSprite, J);}}
}
};