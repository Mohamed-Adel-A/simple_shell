#include "shell.h"

int check_exit(const char *s)
{
	char *exit_s = "exit";
	while (*exit_s)
	{
		if (*s != *exit_s)
			return (-1);
		*s++;
		*exit_s++;
	}
	exit(0);
}

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
	line_cpy = strdup(line);
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

int main(void)
{
	char *line = NULL;
	size_t line_size = 0;
	ssize_t getline_r;
	char **tokens = NULL;
	int n_tokens;



	while (1)
	{
	_puts("($) ");
	line = NULL;
	line_size = 0;
	/*printf("\n %i : %i\n", stdin->_fileno, (int) STDIN_FILENO);*/
	getline_r = _getline(&line, &line_size, stdin);
	if (getline_r == -1)
	{
		exit(EXIT_SUCCESS);
	}
	printf("%lu\n", line_size);
	
	tokens = tokenizing(line);
	printf("%lu\n", line_size);

	/*check_exit(line);*/
	printf("    %s", line);
	free(line);
	}
	return (0);
}
