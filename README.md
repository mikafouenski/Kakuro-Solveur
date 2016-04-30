# [IA] Kakuro solveur

Par Sylvain De Barros et Mickaël Bernardini.

## Description
**Kakuro Solveur** est un projet d'intelligence artificielle de licence 3 
informatique réalisé dans le cadre de la formation. L’application a pour but de 
résoudre une grille de Kakuro au format .txt utilisant les methodes 
[Backtrack](https://en.wikipedia.org/wiki/Backtracking) et 
[Foward-Checking](https://en.wikipedia.org/wiki/Look-ahead_(backtracking))

## Compilation

Aller dans le dossier du projet et compiler avec make:

```console
$ make
```

## Usage

L'application se lance de manière suivante :  
&nbsp;&nbsp;&nbsp;&nbsp;-b : utiliser la méthode Backtrack  
&nbsp;&nbsp;&nbsp;&nbsp;-f : utiliser la méthode Foward-Checking  

suivi du fichier source de la grille de Kakuro, des exemples sont présents dans 
le dossier 'kakuro_grid'.  

ex: Lancer l'application utilisant backtrack sur le fichier ennonce.txt
```console
$ ./kakuro -b kakuro_grid/ennonce.txt
```

## Auteurs

* Sylvain De Barros
* Mickaël Bernardini
