#include "main.h"

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

char **tokenizing(const chr *line)
{
	char token;
	char *delima = " \n";
	char **tokens_local;
	int tokens_count = 0, i = 0;

	if(line == NULL)
		return (NULL);

	token = strtok(line, delima);
	while (token != NULL)
	{
		token_line = strtok(NULL, delima);
		tokens_count++;
	}

	tokens = malloc(tokens_count * sizeof(char *));
	if (tokens == NULL)
		return (NULL);

	token = strtok(line, delima);
	tokens_count = 0;
	while (token != NULL)
	{
		tokens[token_count] = token;
		token = strtok(NULL, delima);
		token_count++;
	}
	tokens[token_count] = token;

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
	/* printf("%lu\n", line_size);*/
	
	n_tokens = tokenizing(line, tokens);

	check_exit(line);
	printf("    %s", line);
	free(line);
	}
	return (0);
}
