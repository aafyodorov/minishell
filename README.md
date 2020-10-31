# minishell

The project was made in collaboration with [aafyodorov](https://github.com/aafyodorov)  

## About

It's a minimum viable version of a real shell.
The main goal is to have a good understanding of process creation and
synchronisation using the C programmming language.

## Installation & Usage

### Building the program
`git clone https://github.com/poringdol/minishell.git && cd minishell && make`

### Running the program
`./minishell` from the project root.

### Description
- Programming language: C
- Implemented a series of builtins: 
  * `echo` (any arguments + `-n` option)
  * `cd` (with/without argument, argument `-`)
  * `export`
  * `unset`
  * `env`
  * `exit`
  * `pwd`
- Errors and `echo $?` handling 
- Double and single quotes handling
- Local and environment variable substitution handling
- Signal management (specifically Ctrl + C, Ctrl + D, Ctrl + \\)
- Multiple commands (semi colons)
- Multiple redirections handling (>, >>, <)
- Multiple pipes handling (|)
- Functions used:
    - malloc, free
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - fork, execve
    - pipe, dup, dup2
    - wait
    - signal
    - exit
    - [libft](https://github.com/poringdol/libft) (own library)  
- No memory leaks
