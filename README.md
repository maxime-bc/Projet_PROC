Maxime BLANCHON

# Rapport du projet PROC : Création et rendu d’automates en SVG

[Sujet](http://web4.ensiie.fr/~christophe.mouilleron/teaching/PROC/projet-suj.pdf)

## I - Installation

Le projet nécessite d'avoir les programmes suivants installés sur sa machine :

- flex et bison (`sudo apt-get install flex bison`),
- un compilateur pour le langage C++.

Pour exécuter le programme, il faut exécuter la commande `make` dans le dossier racine du projet.

## II - Langage utilisé

J'ai débuté le développement du projet avec le langage C. C'est en arrivant à la partie 2, concernant l'export d'un
automate construit par l'utilisateur en un fichier au format SVG, que j'ai décidé de continuer le développement en C++.
En effet, la construction de ce type de fichier en utilisant les données saisies par l'utilisateur allait nécessiter de
multiples manipulations de chaînes de caractères (concaténation, copie, ...), ce qui est plutôt long et fastidieux en C.

Passer au C++ m'a permis d'utiliser le type string, permettant de gérer plus facilement les chaînes de caractères. De
plus, j'ai pu simplifier mon code en utilisant les structures de données déjà implémentées dans le langage comme les
listes, les sets, les tuples...

J'ai ainsi remplacé les listes chaînées que j'utilisais en C pour gérer les nœuds et les transitions par des listes par
le conteneur `list` en C++. Grâce aux structures de données intégrées au langage, j'ai pu simplifier le code et diminuer
le risque d'erreurs liées aux pointeurs utilisés dans mes listes chaînées.

## III - Problèmes rencontrés

J'ai rencontré beaucoup de problèmes au début du projet, liés à la gestion des pointeurs de mes listes chaînées en C.
Ces problèmes m'ont fait perdre du temps et c'est l'une des raisons pour laquelle j'ai décidé d'utiliser pour la
première fois le langage C++. Ce projet aura été pour moi l'occasion d'être introduit à ce langage.

## IV - Améliorations apportées au projet

- Ajout des commandes `CLEAR ALL` et `CLEAR EDGES` : ces commandes ont été ajoutées pour faciliter l'utilisation du
  programme. La commande `CLEAR ALL` permet de supprimer la totalité des nœuds et des transitions stockées au sein du
  programme. La commande `CLEAR EDGES`, quant-à-elle, permet de supprimer la totalité des transitions tout en conservant
  l'ensemble des nœuds.


- Utilisation de la balise `<g>` en SVG pour factoriser les attributs des objets.


