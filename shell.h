#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>

extern char **environ;

/**
 * struct shell_data - struct shell data
 * @line: entered line
 * @tokens: line after tokenizing
 * @wstatus: wait status
 * @cmd_path: string holds path and cmd
 * @cmd_index: enteries indexing
 * @varibles: shell replaced variables
 * @cmd_entered: entered cmd
 */
typedef struct shell_data
{
	char *line;
	char **tokens;
	int wstatus;
	char *cmd_entered;
	char *cmd_path;
	char **varibles;
	unsigned int cmd_index;
} shell_data_t;

/**
 * struct buitins - struct contains builins names and fuctions
 * @name: string contains the command to be used to call the function
 * @function: pointer to the buitin function to be called
 *
 */
typedef struct buitins
{
	char *name;
	int (*function)(shell_data_t *sh_data);
} buitin_t;


/* main.c */
void prompt(void);
void free_all(shell_data_t *sh_data);

/* handle_variables.c */
int handle_variables(shell_data_t *sh_data);

/* utilities */
void handle_signal(int signal_no);

/* comments.c */
int handle_comments(char *line);

/* builtin_cheak.c */
int (*check_builtin(char *cmd))(shell_data_t *sh_data);

/* builtin_exit */
int builtin_exit(shell_data_t *sh_data);
int builtin_cd(shell_data_t *sh_data);

/* atoi.c */
int _isalpha(char c);
int _isdigit(char c);
int _isnumber(const char *str);
int _atoi(const char *str);
char *_itoa(int int_value, char *str);

/* _getline.c file */
int _getchar(FILE *stream);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int getting_line(shell_data_t *sh_data);

/* _puts.c file */
int _putchar(char c);
int _puts(const char *s);


/* strings_functions.c */
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcat(char *dest, const char *src);

/* str2_helper */
int _strchar(const char *str, char c);
char *_strncpy(char *dest, const char *src, int n);


/* mem_helper.c */
void *_memcpy(void *dest, const void *src, size_t n);
void *_realloc(void *ptr, size_t size);

/* tokenizing.c */
char *_strtok(char *s, char *delim);
char **tokenizing(char *line, char *delim);

/* env_helper.c */
char **create_env(void);
void free_env(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

/* env2_helper.c */
int builtin_setenv(shell_data_t *sh_data);
int builtin_unsetenv(shell_data_t *sh_data);
int builtin_env(shell_data_t *sh_data);
void print_env(void);
char *_getenv(const char *variable_name);


/*searchdir.c */
int str_start_with(const char *str, const char *start_str);
int extract_path(const char *str, char *path, char *file_name);
int program_search(const char *fullpath);

/* PATH */
char *check_paths(char *cmd);


#endif
