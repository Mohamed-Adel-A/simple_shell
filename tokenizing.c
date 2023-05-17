#include "shell.h"

/**
 * tokenizing - split string into tokens
 * @line: string to be splited
 *
 * Return: pointer to tokens array
 */
char **tokenizing(char *line)
{
	char *token, *line_cpy;
	char *delim = " \n";
	char **tokens;
	int tokens_count = 0;
	long int token_idx;

	if(line == NULL)
		return (NULL);

	line_cpy = _strdup(line);
	/*strcpy(line_c, line);*/
	token = strtok(line, delim);
	while (token != NULL)
	{
		token = strtok(NULL, delim);
		tokens_count++;		
	}

	tokens = malloc((tokens_count + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	token = strtok(line_cpy, delim);
	tokens_count = 0;
	while (token)
	{
		token_idx = (token - line_cpy);
		tokens[tokens_count] = line + token_idx;
		token = strtok(NULL, delim);
		tokens_count++;
	}
	tokens[tokens_count] = NULL;
	free(line_cpy);

	return (tokens);
}
