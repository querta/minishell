# About minishell
The goal of this project is to write a simple version of a real shell. The main goal is to have a good understanding of process creation and synchronisation using the C programmming language.

#### How to run:
1. Compile with `make`
2. Run `./minishell` from project directory

#### Features:
* Show a prompt when waiting for a command
* Built-in commands: echo, cd, pwd, export, env, unset, exit
* Search and launch the right executable from environment
* Support for quotes, double quotes
* Support pipelines and redirections
* Print, set and unset environment variables
* Support signals ctrl-C, ctrl-D, ctrl-\
* Error management like in bash
