/*
* Author: Luis A. Gutierrez and Victor Huicochea 
* CS 4375
* Date: Feb 28, 2020
* This program is a custom shell for the Unix system. This program mimics the some of the behaviors of the bash shell. 
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