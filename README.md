# LinuxUtils

Ce dépôt contient quelques ressources pour faciliter l'adapation et la réalisation des TP C sous UNIX/Linux.

## Conio
Ce dossier contient une implémentation pour GCC des fonctions `getch()` de Microsoft.

## TerminalUtils
Ce dossier contient un wrapper pour `ncurses` plus simple d'utilisation et qui ressemble à ConsoleTools.

`ncurses` est une bibliothèque de curses qui permet de manipuler les écrans de commandes UNIX/Linux. `ncurses` n'est peut-être pas installé par défaut sur votre ordinateur. Pour ce faire, rapprochez vous de votre gestionnaire de paquet.

| Distribution  | Installation                       |
| ------------- | ---------------------------------- |
| Debian/Ubuntu | `sudo apt-get install ncurses-dev` |
| Fedora        | `sudo dnf install ncurses-devel`   |
| Arch          | `sudo pacman -S ncurses`           |
| OpenSUSE      | `sudo zypper install ncurses`      |
| Gentoo        | `sudo emerge ncurses`              |

## TP-Squelette-v3.0-Linux
Ce dossier contient un portage du sujet du TP6 (année 2020-2021) pour le faire fonctionner sous Linux  
Il suffit d'aller dans ce dossier et de faire :

```bash 
gcc *.c && ./a.out  # Compile et exécute le programme
```

## Makefile

Le fichier Makefile est un fichier de configuration pour la compilation des programmes. Vous pouvez retrouver un exemple de Makefile commenté dans le dossier `Makefile/`.

Pour lancer le Makefile de l'exemple, il suffit d'aller dans le dossier `Makefile/` et de faire :

```bash
make # Compile le programme
```
puis  

```bash
./build/final_program # Exécute le programme
```

ou alors en une ligne 

```bash 
make && ./build/final_program.exe  # Compile et exécute le programme
```

Vous pouvez nettoyer le répertoire de compilation en faisant :

```bash
make clean 
```

### Arborescence à respecter

Pour construire un projet en utilisant ce Makefile, il faut respecter l'arborescence suivante :

    - `src` : contient les fichiers sources du programme

Vous avez un exemple d'arborescence dans le dossier `Makefile`.


pour build et exécuter un projet GCC avec Make, il suffit de mettre les fichiers `.c` et `.h` dans le dossier `src/` et `make` construira le projet à chaque appel  
