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
#include <stddef.h>
#include <fcntl.h>

extern char **environ;

/**
 * struct shell_data - struct shell data
 * @line: entered line
 * @alltokens: all tokens
 * @tokens: line after tokenizing
 * @wstatus: wait status
 * @cmd_path: string holds path and cmd
 * @next_tokens_index: enteries indexing
 * @variables: shell replaced variables
 * @cmd_entered: entered cmd
 * @exit_st: exit status
 * @cmd_idx: cmd index
 * @argv: argv
 * @fd: file descriptor
 * @logical_op: logical op
 * @colon: colon exist if not -1
 * @or: or oprator exitst if not -1
 * @and: and oprator exitst if not -1
 */
typedef struct shell_data
{
	char *line;
	char **alltokens;
	char **tokens;
	int wstatus;
	char *cmd_entered;
	char *cmd_path;
	char **variables;
	int next_tokens_index;
	int exit_st;
	unsigned int cmd_idx;
	char **argv;
	int fd;
	char logical_op;
	int colon;
	int or;
	int and;
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
int check_cmd(shell_data_t *sh_data);
void excuting_cmd(shell_data_t *sh_data, char **argv);
void init_data(shell_data_t *sh_data);


/* errors.c */
int create_error(shell_data_t *sh_data, char *err_msg,
		 int cmd_arg_idx, int file_err);

/* semicolon */
int simicolons_in_str(shell_data_t *sh_data);
int logical_operators_in_str(shell_data_t *sh_data,char operator);
int handle_logical_operators(shell_data_t *sh_data, char *op);

/* free */
void free_loop(shell_data_t *sh_data);
void free_tokens(shell_data_t *sh_data);
void free_all(shell_data_t *sh_data);
void colse_file(shell_data_t *sh_data);

/* handle tokens */
int handle_semicolons(shell_data_t *sh_data);
int loop(shell_data_t *sh_data, char **argv);

/* handle_variables.c */
void free_variables(shell_data_t *sh_data);
int add_variable(char *var, shell_data_t *sh_data);
int check_variable(int token_idx, shell_data_t *sh_data);
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
int _getc(int fd);
ssize_t _getline(char **lineptr, size_t *n, int fd);
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
void *_realloc(void *ptr, size_t size, size_t cpy_size);

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
