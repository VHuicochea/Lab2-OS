// Function declarations for builtin shell commands:
int sh_cd(char **args);
int sh_help(char **args); // Take out
int sh_exit(char **args);
int sh_chprmpt(char **args);
void printDir();
int parsePipe(char* line, char** linePiped);