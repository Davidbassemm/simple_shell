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
char **split_line(char *line);
int launch(char **arguments);
int custom_cd(char **arguments);
int custom_env(char **arguments);
int custom_help(char **arguments);
int custom_exit(char **arguments);
int num_bulitin(char **bulitin);
int execute(char **arguments);
void inter(void);
void non_inter(void);
char *read_stream(void);


#endif
