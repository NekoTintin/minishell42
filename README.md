# MINISHELL 42

---

## Description
Minishell est un projet de shell minimaliste développé dans le cadre de l'école 42.

## Fonctionnalités
- Gestion des commandes externes en absolu, relatif ou dans le `PATH`
- Builtins
	- `echo` avec option `-n` (y compris `-nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn`)
	- `cd` avec uniquement un chemin relatif ou absolu (pas de `cd` sans argument, ni de `cd -` ou `cd ~`)
	- `pwd` sans options
	- `export` sans options (simple export de variables)
	- `unset` sans options
	- `env` sans options ni arguments
	- `exit` sans option (gère l'overflow 😉)
- Gestion des redirections (`<`, `>`, `>>`, `<<`)
- Pipes (`|`)
- Gestion des variables d'environnement et de l'expansion (`$VAR`, `$?`)
- Gestion des quotes simples et doubles (les simples quotes ne font pas d'interprétation).
- Gestion des signaux (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`) (dans le heredoc aussi)

## Installation
Clonez le dépôt puis faire un `make`

```bash
git clone https://github.com/NekoTintin/minishell42.git
cd minishell42
make
```

## Utilisation
Lancez `./minishell` fraichement compilé.

```bash
echo "Hello, world!"
echo -n "Pas de saut de ligne"
cd /tmp
pwd
export MYVAR=42
env
unset MYVAR
exit
echo "test" > fichier.txt
cat fichier.txt | grep "te"
```

## Valgrind
Le fonction Readline en C possède des leaks, il faut utiliser le fichier readline.supp
```bash
valgrind --suppressions=tool/readline.supp --leak-check=full --track-fds=all --show-leak-kinds=all --trace-children=yes ./minishell
```

## Note
Projet validé à 101% (c'était chaud) !

---

## Description
Minishell is a minimalist shell project developed as part of the 42 school curriculum.

## Features
- Execution of external commands with absolute, relative paths or via PATH
- Builtins
  - echo with -n option (including multiple -n like -nnnnnn...)
  - cd with only relative or absolute paths (no cd without argument, nor cd - or cd ~)
  - pwd without options
  - export without options (simple variable export)
  - unset without options
  - env without options or arguments
  - exit without options (handles overflow)
- Handling of redirections (<, >, >>, <<)
- Pipes (|)
- Environment variable handling and expansion ($VAR, $?)
- Handling of single and double quotes (single quotes prevent interpretation)
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\) (also in heredoc)

## Installation
Clone the repository then run `make`
```bash
git clone https://github.com/NekoTintin/minishell42.git
cd minishell42
make
```

## Usage
Run the freshly commpiled `./minishell`

```bash
echo "Hello, world!"
echo -n "Pas de saut de ligne"
cd /tmp
pwd
export MYVAR=42
env
unset MYVAR
exit
echo "test" > fichier.txt
cat fichier.txt | grep "te"
```

## Valgrind
The C Readline function has memory leaks, you must use the readline.supp file

```bash
valgrind --suppressions=tool/readline.supp --leak-check=full --track-fds=all --show-leak-kinds=all --trace-children=yes ./minishell
```

Note
Project validated at 101% (it was tough)!
