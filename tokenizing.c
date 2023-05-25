#include "shell.h"

/***********************************************/
char *_strtok(char *s, char *delim);
char **tokenizing(char *line, char *delim);
/***********************************************/

/**
 * _strtok - convert string to series of tokens
 * @s: string to be converted
 * @delim: dilimits that are used in parsing
 *
 * Return: poiter to the next part, NULL in the end
 */
char *_strtok(char *s, char *delim)
{
	int i;
	static char *current;
	char *start;

	if (delim == NULL)
		return (s);

	if (s != NULL)
	{
		current = s;
	}

	if (s == NULL && current == NULL)
	{
		return (NULL);
	}

	start = current;
	for (i = 0; current[i] != '\0' && (_strchar(delim, current[i]) != -1); i++)
	{
	}

	if (current[i] == '\0')
	{
		start = '\0';
		current = NULL;
		return (NULL);
	}

	start = &current[i];
	for (; current[i] != '\0' ; i++)
	{
		if (_strchar(delim, current[i]) != -1)
			break;
	}

	if (current[i] == '\0')
	{
		current = NULL;
	}
	else
	{
		current[i] = '\0';
		current += (i + 1);
	}

	return (start);
}


/**
 * tokenizing - split string into tokens
 * @line: string to be splited
 * @delim: delimiter to split string upon
 *
 * Return: pointer to tokens array
 */
char **tokenizing(char *line, char *delim)
{
	char *token, *line_cpy, allocated_token;
	/*char *delim = " \n";*/
	char **tokens;
	int tokens_count = 0;
	long int token_idx;

	if (line == NULL)
		return (NULL);

	line_cpy = _strdup(line);
	/*strcpy(line_c, line);*/
	token = _strtok(line, delim);
	while (token != NULL)
	{
		token = _strtok(NULL, delim);
		tokens_count++;
	}

	tokens = malloc((tokens_count + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	token = _strtok(line_cpy, delim);
	tokens_count = 0;
	while (token)
	{
		allocated_token = _strdup(token);
		
		token_idx = (token - line_cpy);
		tokens[tokens_count] = allocated_token;
		token = _strtok(NULL, delim);
		tokens_count++;
	}

	tokens[tokens_count] = NULL;
	free(line_cpy);

	return (tokens);
}




 
 
 
 
