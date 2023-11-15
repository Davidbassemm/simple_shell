#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define EFO 42
extern char **environ;
char *read_line(void);
char **parse_line(char *line);
int launch(char **arguments);
int custom_cd(char **arguments);
int custom_env(char **arguments);
int custom_help(char **arguments);
int custom_exit(char **arguments);
int num_builtin(char **bulitin);
int execute(char **arguments);
void interactive(void);
void non_interactive(void);
char *read_stream(void);


#endif
