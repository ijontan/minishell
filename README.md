# minishell
A project from 42-cursus aims to create a cut-downed version of shell

## usage
to clone the projects
```sh
git clone --recurse-submodules https://github.com/ijontan/minishell.git
```
or
```sh
git clone https://github.com/ijontan/minishell.git
git submodule init
git submodule update
```

to compile
```sh
make
```

to run
```sh
./minishell
```


## debug
to debug a part of the code
1. create a directory test/
2. add a main.c in test/
3. include "minishell.h"
4. add any functions you want to test to the main
5. compile with
```sh
make d
```
6. run with
```sh
./d.out
```
