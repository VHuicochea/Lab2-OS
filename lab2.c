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

// Global Variable for prompt
char *PS1 = "$ ";

// Function to print current directory
void printDir(){
    char cwd[1024];
    char *username = getenv("USER");
    getcwd(cwd, sizeof(cwd));
    printf("\n%s@myShell:~%s %s", username, cwd, PS1);
}

char *sh_read_line(void){
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

int main(){
    printDir();
    printf("Test: %s", sh_read_line());
}
