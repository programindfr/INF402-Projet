# Takuzu

Ce projet fonctionne sur les plateformes Linux, les autres plateformes n'ont pas été testées. Le SAT-solveur utilisé par le projet est `minisat`

## Format de fichier takuzu

L'exécutable principale, `takuzu`, permet de générer un fichier au format `dimacs` à partir d'un fichier au format `takuzu`, de chercher un modèle, puis d'enregistrer la solution dans un fichier au format `takuzu`. La spécification de ce format est la suivante :

```c
n
x##x
xx##
####
###x
```

`n`: taille de la grille carrée

`x`: 0 ou 1

`#`: pour une case vide

## Compilation

Un environnement virtuel python est créé, préservant ainsi votre configuration système. Les outils nécessaire pour compiler et exécuter le projet sont :

- make

- gcc

- python3

- python3-tk

- minisat

```bash
make build
```

## Exécution

L'interface graphique permet de générer un fichier takuzu de la grille, puis de chercher un modèle en appelant l'exécutable `takuzu`. Il est aussi possible d'appeler l'exécutable `takuzu` directement depuis le terminal.

> :warning: input-file: nom de fichier takuzu sans l'extension

```bash
# Interface graphique python
make run

# Exécutable CLI
./dist/takuzu input-file
```

## Organisation

`src`: tous les fichiers sources

`src/include`: spécifications des sources C

`test`: des fichiers d'exemple et de test

`dist`: dossier contenant les exécutables, fichiers objets, fichiers takuzu, fichiers dimacs, environnement virtuel python, créés lors de la compilation et de l'exécution.
