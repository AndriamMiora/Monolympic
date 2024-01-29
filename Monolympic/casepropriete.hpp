
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "joueur.hpp"
#include "casepayante.hpp"
#pragma once
#include <vector>
// Classe dérivée pour les cases propriété
class CasePropriete : public CasePayante {
private:
    int nombreStades;
    int nombrePiscines;
    int nombreSalles;
    int nombreMaxInstallations;


public:
    CasePropriete(int _position, int _cout, bool _estAchete) 
        : CasePayante(_position, _cout, _estAchete),
          nombreStades(0),
          nombrePiscines(0),
          nombreSalles(0),
          nombreMaxInstallations(10) {} // Initialisation par défaut

    // Méthode pour obtenir l'état de la case
    bool getEtat() const {
        return estAchete;
    }

    // Méthode pour obtenir le coût de la case
    int getCout() const {
        return cout;
    }

    // Méthode pour obtenir le nombre de stades
    int getNombreStades() const {
        return nombreStades;
    }

    // Méthode pour obtenir le nombre de piscines
    int getNombrePiscines() const {
        return nombrePiscines;
    }

    // Méthode pour obtenir le nombre de salles
    int getNombreSalles() const {
        return nombreSalles;
    }


    // Méthode pour obtenir le nombre maximal d'installations
    int getNombreMaxInstallations() const {
        return nombreMaxInstallations;
    }

    // Méthode pour mettre à jour l'état de la case
    void setEtat(bool _estAchete) {
        estAchete = _estAchete;
    }

    // Méthode pour mettre à jour le coût de la case
    void setCout(int _cout, int stades, int piscines, int salles) {
        cout = _cout + int(0.8 * 15 * stades + 0.5 * 10 * piscines + 0.25 * 5 * salles);
    }

    // Méthode pour ajouter un stade
    void ajouterStade() {
        if (nombreStades < nombreMaxInstallations) {
            ++nombreStades;
        }
    }

    // Méthode pour ajouter une piscine
    void ajouterPiscine() {
        if (nombrePiscines < nombreMaxInstallations) {
            ++nombrePiscines;
        }
    }

    // Méthode pour ajouter une salle
    void ajouterSalle() {
        if (nombreSalles < nombreMaxInstallations) {
            ++nombreSalles;
        }
    }

    
    // Méthode pour set l'état de la case
    void setEtat(bool _estAchete) const {
        estAchete = _estAchete;
    }

void actionbot (Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points, int nombre1, int nombre2) const override{
    // dem
}
    // Méthode pour effectuer l'action de la case à une position donnée
 void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const override{

    // achete et pas parmis les cases achetées par le joueur (paye le loyer)    
    // achete et parmis les cases achetées par le joueur (demande si veut installer)
    if (J.getPoints() >= cout && !estAchete) {
        // Affichage d'un message au milieu avec fond
        sf::Font font;
        if (!font.loadFromFile("police1.otf")) {
            std::cerr << "Erreur lors du chargement de la police" << std::endl;
        }
        //Bouton acheter et annuler, Chargement de l'image "acheter.png"
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
                            // print la liste des cases achetées par le joueur
                            


                            // Affichage au milieu de la carte de la propriété png
                            sf::Texture texture;
                            if (!texture.loadFromFile("assets/ppt/p" + std::to_string(getPosition()) + ".jpg")) {
                                std::cerr << "Erreur lors du chargement de la texture" << std::endl;
                            }
                            sf::Sprite sprite;
                            sprite.setTexture(texture);
                            sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
                            sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
                           //agrandir la taille de la carte de la propriété
                            

                            // ajouter image pion sur la case
                            sf::Texture texturePion;
                            if (!texturePion.loadFromFile(J.getPion()->getCheminImage())) {
                                std::cerr << "Erreur lors du chargement de la texture" << std::endl;
                            }
                            sf::Sprite spritePion;
                            spritePion.setTexture(texturePion);
                            float facteurRedimensionnement = 0.05f; // Exemple : réduire la taille de moitié
                            spritePion.setScale(facteurRedimensionnement, facteurRedimensionnement);
                            spritePion.setPosition(J.getPion()->getPosition());

                            window.draw(sprite);
                            // attendre 2 secondes
                             window.display();
                            sf::sleep(sf::seconds(5));
                           

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
                    window.clear();
                    return;  // Sortir de la fonction
                }
            }
        }
    }
}

    }
}

};
