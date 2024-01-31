# Monolympic - Monopoly Jeux Olympiques 2024

Bienvenue dans le jeu Monolympic ! Ce jeu est une implémentation du Monopoly en C++ avec l'utilisation de la bibliothèque SFML pour l'interface graphique en thématique des Jeux Olympiques à 2024.

## Auteurs
- @AshleyMAIN ANDRIANARIVO Koloina Ashley
- @AndriamMiora ANDRIAMBOLO-NIVO Miora

## Installation

1. Clonez le dépôt Git en utilisant la commande suivante :
    ```bash
    git clone https://github.com/AndriamMiora/MonopolyJo.git
    ```

2. Assurez-vous d'avoir SFML installé sur votre système en utilisant la commande suivante :
    ```bash
    brew install sfml ou sudo apt-get install libsfml-dev
    ```
 Vous pouvez suivre les instructions sur le site officiel de SFML : [https://www.sfml-dev.org/download/sfml/2.6.1/](https://www.sfml-dev.org/download/sfml/2.6.1/)

3. Déplacez-vous dans le dossier principal du jeu qui est Monolympic où vous trouverez le fichier `Makefile` et exécutez jeu.

## Lancement du Jeu

Après avoir suivi les étapes d'installation, vous pouvez lancer le jeu en exécutant la commande suivante dans le dossier principal :
```bash
make monolympic 
```
ou

```bash
make 
```
Le jeu se lance et vous pouvez commencer à jouer. L'utilisateur peut choisir le pion qu'il veut utiliser pour jouer (entre 2 pions) et il joue contre un bot.
Une partie de jeu dure 15 minutes.

Pour nettoyer les fichiers exécutables après avoir joué, exécuter :

```bash
make clean
```

## Fonctionnalités

![newboard](https://github.com/AndriamMiora/MonopolyJo/assets/125473696/bd98c1b6-0b2a-4e96-84fe-e87f5ec3482a)

- **Plateau du Jeu :** Le plateau du jeu est représenté graphiquement avec différentes cases, chacune ayant une fonctionnalité spécifique.
  
- **Déplacement des Joueurs :** Les joueurs se déplacent sur le plateau en fonction des résultats des lancers de dés.

- **Actions Spécifiques :** Les cases spéciales (Quiz, Chance, Propriété, Service publique, Fermture de ville, Taxe.) déclenchent des actions spécifiques pour les joueurs.

- **Gestion des Propriétés :** Les joueurs peuvent acheter des propriétés avec des prix différents et y constuire des infrastructures olympiques (stade, piscine olmpique et salles omnisports) une fois qu'ils repassent sur la case propriété s'ils ont les moyens et que le site lui appartient. Sinon il peut payer un loyer au propriétaire du site.

- **Gestion des Services Publiques :** Les joueurs peuvent acheter des services publiques ou payer un loyer au propriétaire du service publique.

- **Gestion des Fermetures de Ville :** En tombant sur une case fermeture de ville, le joueur doit payer une amende de 20M pour la réouverture de la ville sinon la ville reste fermée pendant 2 tours. Il existe des cas expetionnels où la ville peut être ouverte si le joueur possède une carte chance ouverture de ville.

- **Gestion des Cartes Chance :** Une fois que le joueur tombe sur une case chance, il peut tirer une carte chance qui peut lui permettre de gagner de l'argent, de perdre de l'argent, de gagner une carte ouverture de ville ou de se déplacer sur une case spécifique.

- **Gestion des Cartes Quiz :** Une fois que le joueur tombe sur une case quiz, il peut tirer une carte quiz qui peut lui permettre de gagner de l'argent si la réponse qu'il donnne est correcte ou de perdre de l'argent si la réponse est fausse.

- **Gestion des Cases Taxe :** Une fois que le joueur tombe sur une case taxe, il doit payer une amende de 10M.

- **Gestion des Cases normales :** Une fois que le joueur tombe sur une case normale, il ne se passe rien.

- **Détermination du Gagnant :** À la fin d'un certain nombre de tours, le joueur avec le plus grand nombre de points (nombre de médailles + loyer des propriétés) gagne la partie.

Amusez-vous bien en jouant au jeu Monolympic !

## Structure du répertoire

Ce répertoire contient les fichiers suivants :

### Fichiers .hpp et .cpp

Ces fichiers définissent les classes utilisés. 

### Dossiers Additionnels

- Le dossier `Assets` contient les images .png utilisées
- Le dossier `tests` comprend le doctest, le TestCase et le `Makefile` associé aux tests

## Tests unitaires

Pour réaliser les tests unitaires, il faut se déplacer dans le dossier tests :

```bash
cd ../tests
```

Et lancer la commande :

```bash
make test
```
