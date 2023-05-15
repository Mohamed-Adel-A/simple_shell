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
	int tokens_count = 0, i = 0;
	long int token_idx;

	if(line == NULL)
		return (NULL);

	printf("strat\n");
	printf("%s\n", line);
	line_cpy = _strdup(line);
	/*strcpy(line_c, line);*/
	token = strtok(line, delim);
	printf("%s\n", line);
	while (token != NULL)
	{
		token_idx = (token - line);
		printf("%i : %s (%s)\n", tokens_count, token, line + token_idx);
		token = strtok(NULL, delim);
		tokens_count++;		
	}

	printf("tokens_count : %i", tokens_count);
	tokens = malloc((tokens_count + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	printf("%s\n", line_cpy);
	token = strtok(line_cpy, delim);
	tokens_count = 0;
	while (token)
	{
		token_idx = (token - line_cpy);
		tokens[tokens_count] = line + token_idx;
		printf("%i : %s (%li)\n", tokens_count, tokens[tokens_count], line_cpy - token);
		token = strtok(NULL, delim);
		tokens_count++;
	}
	tokens[tokens_count] = NULL;
	free(line_cpy);

	return (tokens);
}
