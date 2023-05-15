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
	free(tokens);
	}
	return (0);
}
