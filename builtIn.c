/*
* Author: Luis A. Gutierrez and Victor Huicochea 
* CS 4375
* Date: Feb 28, 2020
* This program is a custom shell for the Unix system. This program mimics some of the behaviors of the bash shell.
* Our shell prints a prompt string specified by the by shell variable PS1 when expecting a command. The default 
* prompt is '$'but can be changed with the command 'chprmpr. Our shell accepts the standard unix command shell syntax
* for specifying commands and parameters. Our shell handles expected user error by using printing statements. Our
* shell provides the follwowing built-in commands: cd, exit, chprmpt. Our shell supports the use of simple pipes. 
*/

// Global Variable for prompt
char *PS1 = "$ ";

// Builtin function implementations

int _chprmpt(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "shell: null input\n");
    }
    PS1 = args[1];

    return 1;
}

int _cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("shell");
        }
    }
    return 1;
}

int myExit(char **args)
{
    return 0;
}