## Projet CY-Météo

Ce projet consiste en une application utilisée pour filtrer, trier et traiter les données météorologiques en fonction des préférences de l'utilisateur.
Il est réalisé à l'aide d'un script en langage Shell et du langage C.
L'affichage de ces données triées permet à l'utilitaire gnuplot de générer des graphiques de type vecteurs, 'carte interpolée' ou de 'barre d'erreur.

## Description du script CY-Meteo.bash

Le script `CY-Meteo.bash` est le cœur du projet. Il est écrit en langage Bash et permet à l'utilisateur de filtrer les données météorologiques, de les trier et de générer des graphiques. Voici un aperçu des fonctionnalités principales du script :

- Filtrage des données en fonction des besoins de l'utilisateur.
- Choix du type de données à traiter (température, pression atmosphérique, vent, humidité, altitude).
- Choix du mode de traitement pour chaque type de données.
- Options de tri (AVL, ABR, liste chaînée ou tableau).
- Gestion des lieux géographiques pour filtrer les données.
- Possibilité de spécifier un intervalle de dates pour limiter les données traitées.
- Communication avec un programme en langage C pour le tri des données.
- Génération de graphiques à partir des données triées.

## Utilisation du script

Pour utiliser le script `CY-Meteo.bash`, suivez les instructions suivantes :

1. Assurez-vous que vous disposez des autorisations nécessaires pour exécuter le script. Par exemple `chmod +x CY-Meteo.bash`
2. Téléchargez le fichier de données météorologiques au format CSV dans le dossier du projet.
3. Exécutez le script en ligne de commande en spécifiant les options désirées.
4. Suivez les instructions affichées par le script pour filtrer les données, choisir les types de données à traiter, spécifier les lieux géographiques, définir les intervalles de dates, etc.
5. Le script générera des graphiques à partir des données triées et les sauvegardera dans un dossier doc.

Pour obtenir de l'aide sur les options disponibles, vous pouvez utiliser l'option `--help`.

## Exemple d'utilisation

Voici un exemple d'utilisation du script :
```bash
./CY-Meteo.bash -f data.csv -p2 -w -A --avl
```
Cette commande permet de générer des graphiques des pressions moyennes et des vents pour les Antilles à partir du fichier de données `data.csv`, en utilisant un tri AVL.

## Manuel Options

[TRIS] : 

-- tab : tri de données à l'aide d'un tableau (ou liste chaînée) 
-- abr : tri à l'aide d'une structure d'arbre binaire ABR ou AVL 
-- avl

[LIEUX] : 

-F : France métropolitaine + Corse.
-G : Guyane française
-S : Saint-Pierre et Miquelon
-A : Antilles
-O : Océan indien
-Q . Antarctique

[TYPE de données] :

- p < pressions atmosphériques >
- t < temperatures >
- w < vent > 
- h < attitude >
- m < humidité >

## Prérequis

Pour exécuter le script, vous avez besoin des logiciels suivants installés sur votre système :

- Bash
- GNU Plot
- Compilateur C (pour le programme de tri en langage C)

## Structure du projet

- `CY-Meteo.bash` : Le script principal.
- `README.md` : Ce fichier qui décrit le projet et son utilisation.
- `data.csv` : Fichier de données météorologiques (non inclus).

N'oubliez pas de remplacer `<nom_fichier>` par le nom réel du fichier de données météorologiques que vous utilisez. Si vous avez des questions ou des problèmes, n'hésitez pas à nous contacter.

Ce README.md peut être enrichi ou ajusté en fonction de vos besoins spécifiques.
  

