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

#include "builtIn.c"

// List of builtin commands, followed by their corresponding functions

char *builtin_str[] = {
    "cd",
    "exit",
    "chprmpt"};

int (*builtin_func[])(char **) = {
    &_cd,
    &myExit,
    &_chprmpt};

int _num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

// Function to print current directory
void _printDir(){
    char cwd[1024];
    char *username = getenv("USER");
    getcwd(cwd, sizeof(cwd));
    printf("\n%s@ourShell:~%s %s", username, cwd, PS1);
}

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
char **_split_line(char *line)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}


int _execute(char **args)
{
    int i;

    if (args[0] == NULL)
    {
        // An empty command was entered
        return 1;
    }

    for (i = 0; i < _num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    return _launch(args);
}

int _launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
            //   perror("aaa");
            printf("ourShell - %s: Command not Found", args[0]);
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        // Error forking
        printf("Program terminated with exit code %d", pid);
    }
    else
    {
        // Parent process
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

// Function to search for pipes
int _parsePipe(char *line, char **linePiped)
{

    for (int i = 0; i < 2; i++)
    {
        linePiped[i] = strsep(&line, "|");
        if (linePiped[i] == NULL)
        {
            break;
        }
    }

    if (linePiped[1] == NULL)
    {
        return 0; // No pipe is found
    }
    else
    {
        return 1; // Pipe found
    }
}

// Pipe Handling
int _piping(char **firstCommand, char **secondCommand){
    int fileDescriptors[2];
    char input_str2[100];


    if(pipe(fileDescriptors) == -1){
        perror("pipe failed");
        return -1;
    }

    if(fork() == 0){ //child 1
        dup2(fileDescriptors[1], STDOUT_FILENO);
        close(fileDescriptors[0]);
        
        execvp(firstCommand[0], firstCommand);
        write(fileDescriptors[1], "dumbass", 10000);
        perror("First program execution failed");
        close(fileDescriptors[1]);
        exit(1);
    }

    if(fork() == 0){ //child 2
             // Pipe:
           
            dup2(fileDescriptors[0], STDIN_FILENO);   // Redirect STDIN to Input part of pipe         
            
            close(fileDescriptors[1]);       //closing pipe write
            close(fileDescriptors[0]);       //close read pipe 

            execvp(secondCommand[0], secondCommand);    // pass the second part of command line as argument
            perror("Second program execution failed");
            exit(1);
        
    }

    close(fileDescriptors[0]);
    close(fileDescriptors[1]);
    wait(0); // Wait for child 1 to finish
    wait(0); // Wait for child 2
    return 1;
}

char *_read_line(void){
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

void _loop(void)
{
    char *line;
    char **args, **firstCommand, **secondCommand;
    int status;
    int pipeFlag;

    char *linePiped[2];

    do
    {
        _printDir();
        line = _read_line();
        // Determine if command contains pipe
        pipeFlag = _parsePipe(line, linePiped);

        if (pipeFlag)
        {
            firstCommand = _split_line(linePiped[0]);
            secondCommand = _split_line(linePiped[1]);
            status = _piping(firstCommand, secondCommand);
            free(firstCommand);
            free(secondCommand);
        } else{
            args = _split_line(line);
            status = _execute(args);
            free(line);
            free(args);
        }
        
    } while (status);
}
