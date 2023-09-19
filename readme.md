# Pipex
## Pipes and redirections
Pipex est un projet en C dans lequel on doit executer une commande shell qui se trouve dans un file descriptor(fichier) puis obtenir son resultat à travers un autre fd(ficher) qui fonctione comme entrée de pipe pour la prochaine commande. Ce pipe nous permet de réexecuter une commande sur le resultat obtenu lors de l'execution de la première commande.
Les fonctions utiles.
+ fork -> creation de nouveau processus (new heap)
+ dup2 -> duplique le file descriptor 1 to 2. (permet la redirection d'entrée/sortie)
+ pipe -> création de deux fichier virtuels pour l'ecriture et lecture entre deux process.

## Installation

```bash
git clone git@github.com:Aggyx/pipex
cd pipex/
make
```
## Usage

```bash
./pipex file1 cmd1 cmd2 file2
```
1. file1 and file2 are file names.
2. cmd1 and cmd2 are shell commands with their parameters.

> [!NOTE]  
> it immitates the following shell command;
>  < file1 cmd1 | cmd2 > file2
***
##BONUS
>Handle multiple pipes.
```
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
Should behave like:
```
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```