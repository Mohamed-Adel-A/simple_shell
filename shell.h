#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


extern char **environ;

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
int _strncmp(char *s1, char *s2, size_t n);


/* mem_helper.c */
void *_memcpy(void *dest, void *src, size_t n);
void *_realloc(void *ptr, size_t size);

/* tokenizing.c */
char **tokenizing(char *line);

/* env_helper.c */
char *_getenv(char *variable_name);


#endif
