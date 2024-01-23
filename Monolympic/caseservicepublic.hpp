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
          nomService(_nomService) {} // Initialisation par défaut

    // Méthode pour obtenir le nom du service public
    std::string getNomService() const {
        return nomService;
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

    // Action à effectuer lorsqu'un joueur tombe sur la case
    void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const {
        if (estAchete) {
            std::cout << "Vous êtes sur la case " << nomService << ". Vous devez payer " << cout << " médailles." << std::endl;
            J.setPoints(J.getPoints() - cout);
        } else {
            if (J.getPoints() >= cout && !estAchete) {
        // Affichage d'un message au milieu avec fond
        sf::Font font;
        if (!font.loadFromFile("police1.otf")) {
            std::cerr << "Erreur lors du chargement de la police" << std::endl;
        }


        //Bouton acheter et annuler
        // Chargement de l'image "acheter.png"
       sf::Texture acheterTexture;
        if (position == 12) {
            if (!acheterTexture.loadFromFile("assets/sp1_acheter.png")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image acheter" << std::endl;
        }
        }
        if (position == 35) {
            if (!acheterTexture.loadFromFile("assets/sp2_acheter.png")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image acheter" << std::endl;
        }
        }
        if (position == 38) {
            if (!acheterTexture.loadFromFile("assets/sp3_acheter.png")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image acheter" << std::endl;
        }
        }

        sf::Sprite acheterSprite;
        acheterSprite.setTexture(acheterTexture);
        acheterSprite.setOrigin(acheterSprite.getLocalBounds().width / 2.0f, acheterSprite.getLocalBounds().height / 2.0f);
        acheterSprite.setPosition(560, 453);  // Position spécifiée pour "acheterSprite"
        acheterSprite.setScale(0.5, 0.5);
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
        if (position == 12) {
            if (!modalTexture.loadFromFile("assets/électricité.jpg")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image modale" << std::endl;
        }
        }
        if (position == 35) {
            if (!modalTexture.loadFromFile("assets/personne.jpg")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image modale" << std::endl;
        }
        }
        if (position == 38) {
            if (!modalTexture.loadFromFile("assets/eau.jpg")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image modale" << std::endl;
        }
        }
        
        sf::Sprite modalSprite;
        modalSprite.setTexture(modalTexture);
        modalSprite.setPosition(450, 160);  // Position spécifiée
        modalSprite.setScale(0.62, 0.62);
        // Affichage du texte à la position spécifiée
        sf::Text coutText;
        coutText.setFont(font);
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
                                    
                    
                            // attendre 2 secondes
                             window.display();
                            sf::sleep(sf::seconds(2));
                           
                            //window.draw(spritePion); // afficher marqueur sur la case achetée
                            // pas être supprime après l'affichage

                                                      
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


        }
    }; 
