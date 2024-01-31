def combinaisons_possibles(x, prix_stade, prix_piscine, prix_salle):
    combinaisons = []
    max_stades = x // prix_stade
    max_piscines = x // prix_piscine
    max_salles = x // prix_salle
    
    for stades in range(max_stades + 1):
        for piscines in range(max_piscines + 1):
            for salles in range(max_salles + 1):
                if stades * prix_stade + piscines * prix_piscine + salles * prix_salle <= x:
                    combinaisons.append((stades, piscines, salles))
    
    return combinaisons

# Exemple d'utilisation
x = int(input("Entrez le montant d'argent disponible : "))  # Montant d'argent disponible
#x =J.getcoins()
prix_stade = 15
prix_piscine = 10
prix_salle = 5

toutes_combinaisons = combinaisons_possibles(x, prix_stade, prix_piscine, prix_salle)
print(f"Avec {x} pièces, voici toutes les combinaisons possibles :")
for combinaison in toutes_combinaisons:
    print(f"Stades = {combinaison[0]}, Piscines = {combinaison[1]}, Salles = {combinaison[2]}")
