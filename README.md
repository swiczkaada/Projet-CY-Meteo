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
2. Téléchargez le fichier `CY-Meteo.bash` sur votre système.
3. Exécutez le script en ligne de commande en spécifiant les options désirées.

## Comment installer et exécuter le projet ?

Instructions de compilation .
1)	Ouvrez l'invite de commande
2)	Déplacez-vous dans le répertoire Projet_Meteo
3)	Exécutez la commande "make" pour générer l'éxécutable
4)	Exécutez la commande "make clean" pour supprimer les fichiers objets
5)	Exécuter la commande I ./scriptshell I sans oublier les arguments.

## Comment utiliser le projet?

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

[FICHIER] :

--help: aide détaillé(affichage) à l'utisation du script
  

