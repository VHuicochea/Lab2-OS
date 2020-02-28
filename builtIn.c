/*
* Author: Luis A. Gutierrez and Victor Huicochea 
* CS 4375
* Date: Feb 28, 2020
* This program is a custom shell for the Unix system. This program mimics the some of the behaviors of the bash shell. 
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