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
    int nombreMaxInstallations;


public:
    CasePropriete(int _position, int _cout, bool _estAchete) 
        : CasePayante(_position, _cout, _estAchete),
          nombreStades(0),
          nombrePiscines(0),
          nombreSalles(0),
          nombreMaxInstallations(10) {} // Initialisation par défaut

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
    // Méthode pour effectuer l'action de la case à une position donnée
 void action(Joueur& J, sf::RenderWindow& window, std::vector<sf::Vector2f> points) const override{

    int positionJoueur = J.getPion()->getPos(); // Supposons que la méthode getPos() retourne la position du joueur
    int cout = getCout(); 

    // Vérifier si la position du joueur correspond à une des cases qu'il a achetées
    bool appartientAuJoueur = false;
    for (int positionCase : J.getCasesAchetees()) {
        if (positionJoueur == positionCase) {
            appartientAuJoueur = true;
            break;
        }
    }
    if (appartientAuJoueur) {
        // La case appartient au joueur
        std::cout << "Le joueur est sur sa propre propriété." << std::endl;
    } else {
        // La case n'appartient pas au joueur
        std::cout << "Le joueur est sur une propriété qui ne lui appartient pas." << std::endl;
    }
    
    // Gestion du Loyer à payer : vérifier si la case est achetée mais n'impartient pas au joueur
  if (estAchete && !appartientAuJoueur) {
    // Chargement de l'image de fond
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/bank.png")) {
            std::cerr << "Erreur lors du chargement de la texture pour l'image bank.png" << std::endl;
            return ;
        }
        // Création de la fenêtre pop-up avec la taille de l'image de fond
        sf::RenderWindow popup(sf::VideoMode(backgroundTexture.getSize().x, backgroundTexture.getSize().y), "Pop-up", sf::Style::Close);

        // Chargement de l'image pour le pop-up
        sf::Texture popupTexture;
        if (!popupTexture.loadFromFile("assets/adversaire.png")) {
            std::cerr << "Erreur lors du chargement de l'image adversaire.png" << std::endl;
            return ;
        }
        sf::Sprite popupSprite(popupTexture);
        popupSprite.setPosition(450, 160);

        // Chargement de l'image pour le bouton fermer
        sf::Texture boutonFermerTexture;
        if (!boutonFermerTexture.loadFromFile("assets/fermer.png")) {
            std::cerr << "Erreur lors du chargement de l'image fermer.png" << std::endl;
            return ;
        }
        sf::Sprite boutonFermerSprite(boutonFermerTexture);
        boutonFermerSprite.setPosition(565, 493); // Position du bouton fermer

            // Boucle principale
        while (popup.isOpen()) {
            sf::Event event;
            while (popup.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    popup.close();
                // Vérifier si un clic a été effectué
                else if (event.type == sf::Event::MouseButtonPressed) {
                    // Récupérer les coordonnées du clic
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;
                    // Vérifier si le clic est sur le bouton fermer
                    if (mouseX >= 585 && mouseX < 585 + boutonFermerTexture.getSize().x &&
                        mouseY >= 493 && mouseY < 493 + boutonFermerTexture.getSize().y) {
                        // Fermer la fenêtre pop-up
                        popup.close();
                    }
                }
            }

            popup.clear();
            // Dessiner le fond en premier
            popup.draw(sf::Sprite(backgroundTexture));
            // Dessiner le pop-up par-dessus
            popup.draw(popupSprite);
            // Dessiner le bouton fermer par-dessus
            popup.draw(boutonFermerSprite);
                // mettre à jour le loyer à payer !! 
            //setCout(getCout(), nombreStades, nombrePiscines, nombreSalles);
            J.setPoints(J.getPoints() - cout);

            // Affichage du coût à payer
            sf::Font font;
            if (!font.loadFromFile("police1.otf")) {
                std::cerr << "Erreur lors du chargement de la police" << std::endl;
                return;
            }
            sf::Text coutText;
            coutText.setFont(font);
            coutText.setString(std::to_string(cout)); // Conversion du coût en chaîne de caractères
            coutText.setCharacterSize(50);
            coutText.setFillColor(sf::Color::Black);
            coutText.setPosition(575, 420); // Position du texte ajustée selon vos besoins
            popup.draw(coutText);

            popup.display();
        }
    }



    // Acheter des installations sur les propriétés du joueur
    if (estAchete && appartientAuJoueur) {
        // Vérification si le joueur a assez de points pour acheter un stade
        if (J.getPoints() >= 5) {
            int nombreSallesxMax = J.getPoints() / 5; // Calcul du nombre maximal de salles pouvant être achetées
            if (J.getPoints() >= 10) {
                int nombrePiscinesMax = J.getPoints() / 10; // Calcul du nombre maximal de piscines pouvant être achetées
                    if (J.getPoints() >= 15) {
                            int nombreStadesMax = J.getPoints() / 15;  // Calcul du nombre maximal de stades pouvant être achetés
                            int nbStadesAchetee = 0; // Initialisation du nombre de stades achetés
                            int nbPiscinesAchetee = 0; // Initialisation du nombre de piscines achetées
                            int nbSallessAchetee = 0; // Initialisation du nombre de salle achetées

                            // Création de la fenêtre pop-up avec l'image de fond
                            sf::Texture backgroundTexture;
                            if (!backgroundTexture.loadFromFile("assets/fondinstallation.png")) {
                                std::cerr << "Erreur lors du chargement de la texture pour l'image fondinstallation.png" << std::endl;
                                return;
                            }
                            sf::Sprite backgroundSprite(backgroundTexture);

                            // Chargement de l'image pour le pop-up (le fichier popupwindow.png contient celui avec les salles)
                            sf::Texture popupTexture;
                            if (!popupTexture.loadFromFile("assets/affichagesanssalle.png")){
                                std::cerr << "Erreur lors du chargement de l'image affichagesanssalle.png" << std::endl;
                                return;
                            }
                            sf::Sprite popupSprite(popupTexture);
                            // Création des sprites pour les images 
                            // Définir la taille des sprites
                            popupSprite.setPosition(450, 160);

                            //Stade

                            // Chargement de l'image stadeplus.png
                            sf::Texture stadeplusTexture;
                            if (!stadeplusTexture.loadFromFile("assets/stadeplus.png")) {
                                std::cerr << "Erreur lors du chargement de l'image stadeplus.png" << std::endl;
                            }
                            sf::Sprite stadeplusSprite(stadeplusTexture);
                            stadeplusSprite.setPosition(675, 417.5);
                            stadeplusSprite.setScale(0.5f, 0.5f); 

                            // Chargement de l'image stademoins.png
                            sf::Texture stademoinsTexture;
                            if (!stademoinsTexture.loadFromFile("assets/stademoins.png")) {
                                std::cerr << "Erreur lors du chargement de l'image stademoins.png" << std::endl;
                            }
                            sf::Sprite stademoinsSprite(stademoinsTexture);
                            stademoinsSprite.setPosition(624, 417.5);
                            stademoinsSprite.setScale(0.5f, 0.5f); 

                            // Piscine
                            // Chargement de l'image piscineplus.png
                            sf::Texture piscineplusTexture;
                            if (!piscineplusTexture.loadFromFile("assets/piscineplus.png")) {
                                std::cerr << "Erreur lors du chargement de l'image piscineplus.png" << std::endl;
                            }
                            sf::Sprite piscineplusSprite(piscineplusTexture);
                            piscineplusSprite.setPosition(675, 442.5);
                            piscineplusSprite.setScale(0.5f, 0.5f);

                            // Chargement de l'image piscinemoins.png
                            sf::Texture piscinemoinsTexture;
                            if (!piscinemoinsTexture.loadFromFile("assets/piscinemoins.png")) {
                                std::cerr << "Erreur lors du chargement de l'image piscinemoins.png" << std::endl;
                            }
                            sf::Sprite piscinemoinsSprite(piscinemoinsTexture);
                            piscinemoinsSprite.setPosition(624, 442.5);
                            piscinemoinsSprite.setScale(0.5f, 0.5f);

                                // Chargement de l'image "annuler.png"
                            sf::Texture annulerTexture;
                            if (!annulerTexture.loadFromFile("assets/annulerpetit.png")) {
                                std::cerr << "Erreur lors du chargement de la texture pour l'image annulerpetit.png" << std::endl;
                                return;
                            }

                            // Chargement de l'image "acheterpetit.png"
                            sf::Texture acheterTexture;
                            if (!acheterTexture.loadFromFile("assets/acheterpetit.png")) {
                                std::cerr << "Erreur lors du chargement de la texture pour l'image acheterpetit.png" << std::endl;
                                return;
                            }
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
                                            if (nbStadesAchetee < nombreStadesMax) {
                                                nbStadesAchetee++;
                                            }
                                        }
                                        // Vérifier le clic sur le bouton stademoins.png
                                        else if (event.mouseButton.x >= 624 && event.mouseButton.x < 624 + stademoinsTexture.getSize().x &&
                                                event.mouseButton.y >= 417.5 && event.mouseButton.y < 417.5 + stademoinsTexture.getSize().y) {
                                            if (nbStadesAchetee > 0) {
                                                nbStadesAchetee--;
                                            }
                                        }
                                        if (event.mouseButton.x >= 675 && event.mouseButton.x < 675 + piscineplusTexture.getSize().x &&
                                            event.mouseButton.y >= 437.5 && event.mouseButton.y < 437.5 + piscineplusTexture.getSize().y) {
                                            if (nbPiscinesAchetee < nombrePiscinesMax) {
                                                nbPiscinesAchetee++;
                                            }
                                        }
                                        // Vérifier le clic sur le bouton piscinemoins.png
                                        else if (event.mouseButton.x >= 624 && event.mouseButton.x < 624 + piscinemoinsTexture.getSize().x &&
                                                event.mouseButton.y >= 437.5 && event.mouseButton.y < 437.5 + piscinemoinsTexture.getSize().y) {
                                            if (nbPiscinesAchetee > 0) {
                                                nbPiscinesAchetee--;
                                            }
                                        }
                                        if (acheterSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                            J.setPoints(J.getPoints() - (nbStadesAchetee * 15 + 10 * nbPiscinesAchetee));
                                            // Ferme la fenêtre pop-up
                                            popup.close();
                                            reponse = true;
                                            // Confirme les modifications et l'achat
                                            // Met à jour le nombre de stades
                                            nombreStades += nbStadesAchetee;
                                            nombrePiscines += nbPiscinesAchetee;

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
                                popup.draw(piscineplusSprite); // Dessiner le bouton d'ajout de piscine
                                popup.draw(piscinemoinsSprite); // Dessiner le bouton de suppression de piscine
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
                                nbStadesText.setString(std::to_string(nbStadesAchetee));
                                //std::cout << "Nombre de achetés sur la case : " << nbStadesAchetee << std::endl;
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
                                nbPiscinesText.setString(std::to_string(nbPiscinesAchetee));
                                nbPiscinesText.setCharacterSize(12);
                                nbPiscinesText.setFillColor(sf::Color::Black);
                                nbPiscinesText.setPosition(piscineplusSprite.getPosition().x-19, piscineplusSprite.getPosition().y); // Position ajustée
                                

                                sf::Text nbPiscinesSurCaseText;
                                nbPiscinesSurCaseText.setFont(font);
                                nbPiscinesSurCaseText.setString(std::to_string(nombrePiscines));
                                nbPiscinesSurCaseText.setCharacterSize(12);
                                nbPiscinesSurCaseText.setFillColor(sf::Color::Black);
                                nbPiscinesSurCaseText.setPosition(piscineplusSprite.getPosition().x + 50, piscineplusSprite.getPosition().y); // Position ajustée
                                
                                popup.draw(nbStadesText);
                                popup.draw(nbPiscinesText);
                                popup.draw(nbPiscinesSurCaseText);
                                popup.draw(nbStadesSurCaseText);
                                popup.display();
                            }
                        }

                    }
                }
                    
        }

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
                    return;  // Sortir de la fonction
                }
            }
        }
    }
}

    }
}

};