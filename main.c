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

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "lab2.h"
#include "lab2.c"

int main(int argc, char **argv)
{

    // Command loop
    _loop();

    return EXIT_SUCCESS;
}