#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "case.hpp"
#include "joueur.hpp"
#include "casepayante.hpp"
#pragma once
#include <vector>
// Classe dérivée pour les cases propriété
class CasePropriete : public CasePayante {
private:
    mutable int nombreStades;
    mutable int nombrePiscines;
    mutable int nombreSalles;
    mutable int loyerPaye;
public:
    CasePropriete(int _position, int _cout, bool _estAchete) 
        : CasePayante(_position, _cout, _estAchete),
          nombreStades(0),
          nombrePiscines(0),
          nombreSalles(0){}
            

     std::string getPositionTexte() const {
        return "Position de la case : " + std::to_string(getPosition());
    }
    
    // Méthode pour obtenir l'état de la case
    bool getEtat() const {
        return estAchete;
    }

    // Méthode pour obtenir le coût de la case
    int getCout() const override {
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

    // Méthode pour mettre à jour l'état de la case
    void setEtat(bool _estAchete) {
        estAchete = _estAchete;
    }
  
    // Méthode pour set l'état de la case
    void setEtat(bool _estAchete) const {
        estAchete = _estAchete;
    }


// fonction qui paie le loyer si la case n'appartient pas au joeur

void payerLoyer(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const {
    sf::Texture backgroundTexture, popupTexture, boutonFermerTexture;
    backgroundTexture.loadFromFile("assets/bank.png") ; popupTexture.loadFromFile("assets/adversaire.png");
    boutonFermerTexture.loadFromFile("assets/fermer.png");
    sf::Sprite popupSprite(popupTexture), boutonFermerSprite(boutonFermerTexture);
    popupSprite.setPosition(450, 160);
    boutonFermerSprite.setPosition(565, 493);
    sf::RenderWindow popup(sf::VideoMode(backgroundTexture.getSize().x, backgroundTexture.getSize().y), "Pop-up", sf::Style::Close);
    while (popup.isOpen()) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                popup.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                int mouseX = event.mouseButton.x, mouseY = event.mouseButton.y;
                if (mouseX >= 585 && mouseX < 585 + boutonFermerTexture.getSize().x &&
                    mouseY >= 493 && mouseY < 493 + boutonFermerTexture.getSize().y)
                    popup.close();
            }
        }
        popup.clear(); popup.draw(sf::Sprite(backgroundTexture));
        popup.draw(popupSprite); popup.draw(boutonFermerSprite);
        int newCout = getCout() + int((0.8 * 15 * getNombreStades()) + (0.5 * 10 * getNombrePiscines()) + (0.25 * 5 * getNombreSalles()));
        J.setPoints(std::max(0, J.getPoints() - newCout));
        sf::Font font; font.loadFromFile("police1.otf");
        sf::Text coutText(std::to_string(getCout()), font, 50);
        coutText.setFillColor(sf::Color::Black);
        coutText.setPosition(575, 420);
        popup.draw(coutText);
        popup.display();
    }
}


void payerLoyerBot(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const{
 int newcout = getCout() + int((0.8 * 15 * getNombreStades()) + (0.5 * 10 * getNombrePiscines())+ (0.25 * 5 * getNombreSalles()));
            if (J.getPoints()>newcout){
                J.setPoints(J.getPoints() - newcout);
            }else {
                J.setPoints(0);
            }

}

void achatInstallation(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const {
     // Vérification si le joueur a assez de points pour acheter un stade
        if (J.getPoints() >= 5) {
            int nombreSallesxMax = J.getPoints() / 5; // Calcul du nombre maximal de salles pouvant être achetées
            if (J.getPoints() >= 10) {
                int nombrePiscinesMax = J.getPoints() / 10; // Calcul du nombre maximal de piscines pouvant être achetées
                    if (J.getPoints() >= 15) {
                            int nombreStadesMax = J.getPoints() / 15;  // Calcul du nombre maximal de stades pouvant être achetés
                            int nbStadesAchetes = 0;//std::min(nombreStadesMax, J.getPoints() / 15); // Achète le maximum de stades possible
                            int nbPiscinesAchetes = 0;//std::min(nombrePiscinesMax, (J.getPoints() - nbStadesAchetes * 15) / 10); // Achète le maximum de piscines possible
                            int nbSallesAchetes = 0;//std::min(nombreSallesxMax, (J.getPoints() - nbStadesAchetes * 15 - nbPiscinesAchetes * 10) / 5); // Achète le maximum de salles possible

                            // Création de la fenêtre pop-up avec l'image de fond
                            sf::Texture backgroundTexture;
                            backgroundTexture.loadFromFile("assets/fondinstallation.png");
                            sf::Sprite backgroundSprite(backgroundTexture);

                            // Chargement de l'image pour le pop-up (le fichier popupwindow.png contient celui avec les salles)
                            sf::Texture popupTexture;
                            popupTexture.loadFromFile("assets/popupwindow.png");
                            sf::Sprite popupSprite(popupTexture);
                            // Création des sprites pour les images 
                            // Définir la taille des sprites
                            popupSprite.setPosition(450, 160);

                            //Stade

                            // Chargement de l'image stadeplus.png
                            sf::Texture stadeplusTexture;
                            stadeplusTexture.loadFromFile("assets/stadeplus.png");
                            sf::Sprite stadeplusSprite(stadeplusTexture);
                            stadeplusSprite.setPosition(675, 417.5);
                            stadeplusSprite.setScale(0.5f, 0.5f); 

                            // Chargement de l'image stademoins.png
                            sf::Texture stademoinsTexture;
                            stademoinsTexture.loadFromFile("assets/stademoins.png");
                            sf::Sprite stademoinsSprite(stademoinsTexture);
                            stademoinsSprite.setPosition(624, 417.5);
                            stademoinsSprite.setScale(0.5f, 0.5f); 

                            // Piscine
                            // Chargement de l'image piscineplus.png
                            sf::Texture piscineplusTexture;
                            piscineplusTexture.loadFromFile("assets/piscineplus.png");
                            sf::Sprite piscineplusSprite(piscineplusTexture);
                            piscineplusSprite.setPosition(675, 442.5);
                            piscineplusSprite.setScale(0.5f, 0.5f);

                            // Chargement de l'image piscinemoins.png
                            sf::Texture piscinemoinsTexture;
                            piscinemoinsTexture.loadFromFile("assets/piscinemoins.png");
                            sf::Sprite piscinemoinsSprite(piscinemoinsTexture);
                            piscinemoinsSprite.setPosition(624, 442.5);
                            piscinemoinsSprite.setScale(0.5f, 0.5f);

                            //Salles 
                            // Chargement de l'image piscineplus.png
                            sf::Texture salleplusTexture;
                            salleplusTexture.loadFromFile("assets/salleplus.png");
                            sf::Sprite salleplusSprite(salleplusTexture);
                            salleplusSprite.setPosition(675, 467.5);
                            salleplusSprite.setScale(0.5f, 0.5f);

                            // Chargement de l'image sallemoins.png
                            sf::Texture sallemoinsTexture;
                            sallemoinsTexture.loadFromFile("assets/sallemoins.png");
                            sf::Sprite sallemoinsSprite(sallemoinsTexture);
                            sallemoinsSprite.setPosition(624, 467.5);
                            sallemoinsSprite.setScale(0.5f, 0.5f);
                           // Chargement de l'image "annuler.png"
                            sf::Texture annulerTexture;
                            annulerTexture.loadFromFile("assets/annulerpetit.png");
                            // Chargement de l'image "acheterpetit.png"
                            sf::Texture acheterTexture;
                            acheterTexture.loadFromFile("assets/acheterpetit.png"); 
                            // Création des sprites pour les boutons "annuler.png" et "acheter.png"
                            sf::Sprite annulerSprite(annulerTexture);
                            annulerSprite.setPosition(585, 513); // Position spécifiée pour "annuler.png"
                            sf::Sprite acheterSprite(acheterTexture);
                            acheterSprite.setPosition(585, 493); // Position spécifiée pour "acheter.png"
                            
                            bool reponse = false;
                            // Boucle principale de la fenêtre pop-up
                            sf::RenderWindow popup(sf::VideoMode(backgroundTexture.getSize().x, backgroundTexture.getSize().y), "Pop-up", sf::Style::Close);
                            while (popup.isOpen()) {
                                sf::Event event;
                                while (popup.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed) {
                                        popup.close();
                                    }

                                    else if (event.type == sf::Event::MouseButtonPressed) {
                                        // Vérifier le clic sur le bouton stadeplus.png
                                        if (event.mouseButton.x >= 675 && event.mouseButton.x < 675 + stadeplusTexture.getSize().x &&
                                            event.mouseButton.y >= 417.5 && event.mouseButton.y < 417.5 + stadeplusTexture.getSize().y) {
                                            if (nbStadesAchetes < nombreStadesMax && (nbStadesAchetes * 15 + nbPiscinesAchetes * 10 + nbSallesAchetes * 5) < J.getPoints()) {
                                                nbStadesAchetes++;
                                            }
                                        }
                                        // Vérifier le clic sur le bouton stademoins.png
                                        else if (event.mouseButton.x >= 624 && event.mouseButton.x < 624 + stademoinsTexture.getSize().x &&
                                                event.mouseButton.y >= 417.5 && event.mouseButton.y < 417.5 + stademoinsTexture.getSize().y) {
                                            if (nbStadesAchetes > 0) {
                                                nbStadesAchetes--;
                                            }
                                        }
                                        // Vérifier le clic sur le bouton piscineplus.png
                                        if (event.mouseButton.x >= 675 && event.mouseButton.x < 675 + piscineplusTexture.getSize().x &&
                                            event.mouseButton.y >= 437.5 && event.mouseButton.y < 437.5 + piscineplusTexture.getSize().y) {
                                            if (nbPiscinesAchetes < nombrePiscinesMax && (nbStadesAchetes * 15 + nbPiscinesAchetes * 10 + nbSallesAchetes * 5) < J.getPoints()) {
                                                nbPiscinesAchetes++;
                                            }
                                        }
                                        // Vérifier le clic sur le bouton piscinemoins.png
                                        else if (event.mouseButton.x >= 624 && event.mouseButton.x < 624 + piscinemoinsTexture.getSize().x &&
                                                event.mouseButton.y >= 437.5 && event.mouseButton.y < 437.5 + piscinemoinsTexture.getSize().y) {
                                            if (nbPiscinesAchetes > 0) {
                                                nbPiscinesAchetes--;
                                            }
                                        }
                                        // Vérifier le clic sur le bouton salleplus.png
                                        if (event.mouseButton.x >= 675 && event.mouseButton.x < 675 + salleplusTexture.getSize().x &&
                                            event.mouseButton.y >= 467.5 && event.mouseButton.y < 467.5 + salleplusTexture.getSize().y) {
                                            if (nbSallesAchetes < nombreSallesxMax && (nbStadesAchetes * 15 + nbPiscinesAchetes * 10 + nbSallesAchetes * 5) < J.getPoints()) {
                                                nbSallesAchetes++;
                                            }
                                        }
                                        // Vérifier le clic sur le bouton sallemoins.png
                                        else if (event.mouseButton.x >= 624 && event.mouseButton.x < 624 + sallemoinsTexture.getSize().x &&
                                                event.mouseButton.y >= 467.5 && event.mouseButton.y < 467.5 + sallemoinsTexture.getSize().y) {
                                            if (nbSallesAchetes > 0) {
                                                nbSallesAchetes--;
                                            }
                                        }
                                   
                                        if (acheterSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                             // Déduire le coût total des points du joueur
                                            int coutTotal = nbStadesAchetes * 15 + nbPiscinesAchetes * 10 + nbSallesAchetes * 5;
                                            J.setPoints(J.getPoints() - coutTotal);
                                            // Ferme la fenêtre pop-up
                                            popup.close();
                                            reponse = true;
                                            // Confirme les modifications et l'achat
                                            // Met à jour le nombre de stades
                                            nombreStades += nbStadesAchetes;
                                            nombrePiscines += nbPiscinesAchetes;
                                            nombreSalles += nbSallesAchetes;
                                        }
                                        // Vérifie le clic sur le bouton "annuler.png"
                                        else if (annulerSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                            reponse = false;
                                            // Ferme la fenêtre pop-up sans rien modifier
                                            popup.close();
                                        }

                                    }
                                }
                                // Effacer et redessiner la fenêtre pop-up avec le fond et le pop-up
                                popup.clear();
                                popup.draw(backgroundSprite); // Dessiner le fond en premier
                                popup.draw(popupSprite); // Dessiner le pop-up par-dessus
                                popup.draw(stadeplusSprite);
                                popup.draw(stademoinsSprite);
                                popup.draw(piscineplusSprite);
                                popup.draw(piscinemoinsSprite); 
                                popup.draw(salleplusSprite); 
                                popup.draw(sallemoinsSprite);
                                popup.draw(annulerSprite);
                                popup.draw(acheterSprite);
                    
                                // Affichage du nombre de stades achetés
                                sf::Font font;
                                if (!font.loadFromFile("police1.otf")) {
                                    std::cerr << "Erreur lors du chargement de la police" << std::endl;
                                    return;
                                }
                                sf::Text nbStadesText;
                                nbStadesText.setFont(font);
                                nbStadesText.setString(std::to_string(nbStadesAchetes));
                                //std::cout << "Nombre de achetés sur la case : " << nbStadesAchetes<< std::endl;
                                nbStadesText.setCharacterSize(12);
                                nbStadesText.setFillColor(sf::Color::Black);
                                nbStadesText.setPosition(655, 419); // Position spécifiée
                                
                                sf::Text nbStadesSurCaseText;
                                nbStadesSurCaseText.setFont(font);
                                nbStadesSurCaseText.setString(std::to_string(nombreStades));
                                //std::cout << "Nombre de stades sur la case : " << nombreStades << std::endl;
                                nbStadesSurCaseText.setCharacterSize(12);
                                nbStadesSurCaseText.setFillColor(sf::Color::Black);
                                nbStadesSurCaseText.setPosition(725, 419); // Position spécifiée, ajustez selon vos besoins

                                sf::Text nbPiscinesText;
                                nbPiscinesText.setFont(font);
                                nbPiscinesText.setString(std::to_string(nbPiscinesAchetes));
                                nbPiscinesText.setCharacterSize(12);
                                nbPiscinesText.setFillColor(sf::Color::Black);
                                nbPiscinesText.setPosition(piscineplusSprite.getPosition().x-19, piscineplusSprite.getPosition().y); // Position ajustée
                                

                                sf::Text nbPiscinesSurCaseText;
                                nbPiscinesSurCaseText.setFont(font);
                                nbPiscinesSurCaseText.setString(std::to_string(nombrePiscines));
                                nbPiscinesSurCaseText.setCharacterSize(12);
                                nbPiscinesSurCaseText.setFillColor(sf::Color::Black);
                                nbPiscinesSurCaseText.setPosition(piscineplusSprite.getPosition().x + 50, piscineplusSprite.getPosition().y); // Position ajustée
                                
        
                                sf::Text nbSallesText;
                                nbSallesText.setFont(font);
                                nbSallesText.setString(std::to_string(nbSallesAchetes));//nbSallesAchetes

                                nbSallesText.setCharacterSize(12);
                                nbSallesText.setFillColor(sf::Color::Black);
                                nbSallesText.setPosition(salleplusSprite.getPosition().x-19, salleplusSprite.getPosition().y); // Position ajustée

                                sf::Text nbSallesSurCaseText;
                                nbSallesSurCaseText.setFont(font);
                                nbSallesSurCaseText.setString(std::to_string(nombreSalles));//nombreSalles
                                nbSallesSurCaseText.setCharacterSize(12);
                                nbSallesSurCaseText.setFillColor(sf::Color::Black);
                                nbSallesSurCaseText.setPosition(salleplusSprite.getPosition().x + 50, salleplusSprite.getPosition().y); // Position ajustée

                            
                                popup.draw(nbStadesText);
                                popup.draw(nbPiscinesText);
                                popup.draw(nbPiscinesSurCaseText);
                                popup.draw(nbStadesSurCaseText);
                                popup.draw(nbSallesText);
                                popup.draw(nbSallesSurCaseText);
                                popup.display();
                            }
                        }

                    }
                }
            }

void handlePptsJoueur(sf::RenderWindow& window, sf::Sprite& acheterSprite, sf::Sprite& annulerSprite, Joueur& J, bool& reponse) const {
    while (!reponse) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return; }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (acheterSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                        reponse = true;
                        J.setPoints(J.getPoints() - cout); setEtat(true);
                        std::vector<int> casesAchetees = J.getCasesAchetees();
                        casesAchetees.push_back(getPosition());
                        J.setCasesAchetees(casesAchetees);

                        sf::Texture texture;
                        texture.loadFromFile("assets/ppt/p" + std::to_string(getPosition()) + ".jpg");
                        sf::Sprite sprite; sprite.setTexture(texture);
                        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
                        sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

                        sf::Texture texturePion; texturePion.loadFromFile(J.getPion()->getCheminImage());
                        sf::Sprite spritePion; spritePion.setTexture(texturePion);
                        float facteurRedimensionnement = 0.05f;
                        spritePion.setScale(facteurRedimensionnement, facteurRedimensionnement);
                        spritePion.setPosition(J.getPion()->getPosition());
                        window.draw(sprite); window.display(); sf::sleep(sf::seconds(5));}
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (annulerSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        reponse = false; return;
                    }
                }
            }
        }
    }
}

    // fonction qui achète les ppts 
void achatsppts (Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const {
        sf::Font font; font.loadFromFile("police1.otf");
        //Bouton acheter et annuler
        sf::Texture acheterTexture; acheterTexture.loadFromFile("assets/acheter.png");
        sf::Sprite acheterSprite;
        acheterSprite.setTexture(acheterTexture);
        acheterSprite.setOrigin(acheterSprite.getLocalBounds().width / 2.0f, acheterSprite.getLocalBounds().height / 2.0f);
        acheterSprite.setPosition(560, 453);  // Position spécifiée pour "acheterSprite"

        sf::Texture annulerTexture; annulerTexture.loadFromFile("assets/annuler.png");
        sf::Sprite annulerSprite;
        annulerSprite.setTexture(annulerTexture);
        annulerSprite.setOrigin(annulerSprite.getLocalBounds().width / 2.0f, annulerSprite.getLocalBounds().height / 2.0f);
        annulerSprite.setPosition(670, 453);  // Position spécifiée pour "annulerSprite

        sf::Texture modalTexture;
        modalTexture.loadFromFile("assets/modalproprietenew.png");
        sf::Sprite modalSprite; modalSprite.setTexture(modalTexture);
        modalSprite.setPosition(450, 160);  // Position spécifiée
    
        sf::Text coutText; coutText.setFont(font);
        coutText.setString(std::to_string(cout));
        coutText.setCharacterSize(10); coutText.setFillColor(sf::Color::Black);
        coutText.setPosition(645, 403);  // Position spécifiée
        // Affichage
        window.draw(modalSprite); window.draw(coutText);
        window.draw(annulerSprite); window.draw(acheterSprite);  
        window.display();
        bool reponse = false;  // Boucle pour attendre la réponse du joueur
        handlePptsJoueur(window, acheterSprite, annulerSprite, J, reponse); // Attendre la réponse du joueur pour acheter ou non
}

void achatInstallationBot(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const {
    // Vérification si le joueur a assez de points pour acheter un stade
    if (J.getPoints() >= 5) {
        int nombreSallesxMax = J.getPoints() / 5; // Calcul du nombre maximal de salles pouvant être achetées
        if (J.getPoints() >= 10) {
            int nombrePiscinesMax = J.getPoints() / 10; // Calcul du nombre maximal de piscines pouvant être achetées
            if (J.getPoints() >= 15) {
                // Achat du maximum d'installations sans dépasser le nombre de points
                int nombreStadesMax = J.getPoints() / 15;  // Calcul du nombre maximal de stades pouvant être achetés
                int nbStadesAchetes = std::min(nombreStadesMax, J.getPoints() / 15); // Achète le maximum de stades possible
                int nbPiscinesAchetes = std::min(nombrePiscinesMax, (J.getPoints() - nbStadesAchetes * 15) / 10); // Achète le maximum de piscines possible
                int nbSallesAchetes = std::min(nombreSallesxMax, (J.getPoints() - nbStadesAchetes * 15 - nbPiscinesAchetes * 10) / 5); // Achète le maximum de salles possible

                // Met à jour le nombre de stades, piscines, et salles
                nombreStades += nbStadesAchetes;
                nombrePiscines += nbPiscinesAchetes;
                nombreSalles += nbSallesAchetes;

                // Déduire le coût total des points du joueur
                int coutTotal = nbStadesAchetes * 15 + nbPiscinesAchetes * 10 + nbSallesAchetes * 5;
                J.setPoints(J.getPoints() - coutTotal);
            }
        }
    }
}

void achatpptsbot(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const {
    int nombrealeatoire = rand() % 2;
    if (nombrealeatoire == 0) {
        J.setPoints(J.getPoints() - cout); setEtat(true);
        std::vector<int> casesAchetees = J.getCasesAchetees();
        casesAchetees.push_back(getPosition());
        J.setCasesAchetees(casesAchetees);
        sf::sleep(sf::seconds(5));
    }
}
    // Méthode pour effectuer l'action de la case à une position donnée
void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const override{
    int positionJoueur = J.getPion()->getPos(); // Supposons que la méthode getPos() retourne la position du joueur
    int cout = getCout(); 
    bool appartientAuJoueur = false;
    for (int positionCase : J.getCasesAchetees()) {    // Vérifier si la position du joueur correspond à une des cases qu'il a achetées
        if (positionJoueur == positionCase) {
            appartientAuJoueur = true;
            break;
        }
    }
  if (estAchete && !appartientAuJoueur){    // Gestion du Loyer à payer : vérifier si la case est achetée mais n'impartient pas au joueur
    if (J.getBot() == false){
        payerLoyer(J, window, points);
    }
    else { payerLoyerBot(J, window, points);}
  }
    if (estAchete && appartientAuJoueur) {     // Acheter des installations sur les propriétés du joueur
        if (J.getBot() == false){
            achatInstallation(J, window, points);
        }
        else { achatInstallationBot(J, window, points);
        }
    }
    if (J.getPoints() >= cout && !estAchete) { // Vérifier si le joueur a assez de points pour acheter la case
       if (J.getBot() == false){
         achatsppts(J, window, points);
    }
    else { achatpptsbot(J, window, points);
       }
    }
}

};