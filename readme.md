# Projet Roborally

Ce projet vise à créer un joueur automatique pour le jeu [Roborally](https://fr.wikipedia.org/wiki/RoboRally). 
Le sujet est disponible en pdf [sur la page du cours](https://liris.cnrs.fr/vincent.nivoliers/lifap6/Supports/Projet/roborally.pdf).

La solution proposée implémente les algorithme de Dijkstra et A* afin de trouver les plus courts chemins d'un point a à un point b.
La recherche peut se faire directement depus le graph ou via un joueur artificiel qui dispose d'un set limité de cartes.

Les plateaux sont contenus dans le dossier "Data" (la démo utilise board.txt).

Pour compiler et utiliser le projet :
- Se rendre dans le dossier Src
- Executer la commande "make" (ou plus précisemment "make demo" / "make app")
- Pour lancer l'application web, saisir "./app ../Data/[nom_pleateau]"
- Pour lancer la démonstration des algoritmes de recherche de chemin, saisir "./demo"