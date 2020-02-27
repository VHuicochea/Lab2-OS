/*
* Author: Luis A. Gutierrez
* CS 4375
* Date: Feb 28, 2020
* This program is a custom shell for the Unix system. This program mimics the some of the behaviors of the bash shell. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> //to get contents of current directory (ls)
#include <unistd.h> //to change directory (cd)

char input[101];
char working_dir[1024];

int main(int argc, char *agrv){
    init_shell();
    printWorkingDir();
    printWorkingDirContents();
    getInput();

    return 0;
}

void init_shell(){
    printf("\n\n***********************");
    printf("\n* Welcome to My Shell *");
    printf("\n***********************\n\n");
}

void printWorkingDir(){
    getcwd(working_dir, sizeof(working_dir));
    printf("Dir: %s\n", working_dir);
}

void getInput(){
    printf("%s@myShell:~$ ", getenv("USER")); //print shell prompt
    fgets(input, 101, stdin); //save the input
    printf("%s\n", input);
}

void printWorkingDirContents(){ //simulate ls command
    struct dirent *directory;

    DIR *dr = opendir("."); 

    if (dr == NULL){
        printf("Could not open current directory");
        return 0;
    }

    while((directory = readdir(dr)) != NULL){
        printf("%s ", directory->d_name);
    }
    
    printf("\n");

    closedir(dr);-
    
}



void changeCurrentDir(){ //simulate cd command
    
}

void commandHandler(){
    int numOfCommands = 4;
    char* listOfCommands[numOfCommands];

    listOfCommands[0] = "help";
    listOfCommands[1] = "exit";
    listOfCommands[2] = "ls";
    listOfCommands[3] = "cd";

}