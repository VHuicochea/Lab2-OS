// Function declarations for builtin shell commands:
int _cd(char **args);
int myExit(char **args);
int _chprmpt(char **args);
void _printDir();
char **_split_line(char *line);
char *_read_line(void);
int _execute(char **args);
int _launch(char **args);
int _piping(char **firstCommand, char **secondCommand);
int _parsePipe(char *line, char **linePiped);
void _loop(void);
