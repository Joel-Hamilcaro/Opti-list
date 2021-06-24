# OptiList  

<img alt="C" src="https://img.shields.io/badge/c%20-%2300599C.svg?&style=flat-square&logo=c&logoColor=white"/>   


*Projet réalisé en binôme dans le cadre du cours "Langage C"*   
**Auteurs : [Joël Hamilcaro](https://github.com/Joel-Hamilcaro/) et [Jie Tu](https://github.com/jie-tu)**

Le but du projet est d’implémenter des listes chaînées génériques en langage C. Ces listes doivent être conçues de sorte à limiter le nombre d’appel à malloc et comparer l’efficacité de cette implémentation avec l’implémentation d'une liste "classique".

## Compiler :

Dans le dossier contenant le fichier **Makefile**,
ouvrir un terminal et faire la commande `make`.


## Lancer le programme

Faire la commande : `./launcher arg1 arg2 arg3 arg4`

arg1 : Nombre d'opération à tester
arg2 : Option d'affichage
    - 0 pour ne rien afficher
    - 1 pour afficher la liste à la fin des tests
    - 2 pour afficher la liste à chaque étape
arg3 : Liste à tester
    - 0 pour la liste du projet2019.c
    - 1 pour comparer avec une liste classique (qui fait malloc tout le temps).
arg4 : Mémoire à allouer pour le premier malloc de memory (inutile si arg3==1).

#### Test de fuite de mémoire

`valgrind --leak-check=yes ./launcher arg1 arg2 arg3 arg4`

#### Test de vitesse

`time ./launcher arg1 arg2 arg3 arg4`

## Effacer les fichiers .o et exécutables

Dans le dossier contenant le fichier **Makefile**,
ouvrir un terminal et faire la commande `make clean`.
