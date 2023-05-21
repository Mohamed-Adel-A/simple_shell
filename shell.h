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

extern char **environ;


/* atoi.c */
int _isnumber(const char *str);
int _atoi(const char *str);
char *_itoa(int int_value, char *str);

/* _getline.c file */
int _getchar(FILE *stream);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

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


/* mem_helper.c */
void *_memcpy(void *dest, const void *src, size_t n);
void *_realloc(void *ptr, size_t size);

/* tokenizing.c */
char **tokenizing(char *line, char *delim);

/* env_helper.c */
char **create_env();
void free_env();
void print_env();
char *_getenv(const char *variable_name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);


/*searchdir.c */
int str_start_with(const char *str, const char *start_str);
int extract_path(const char *str, char *path, char *file_name);
int program_search(const char *fullpath);

/* PATH */
/*char *check_paths(char *cmd);*/


#endif
