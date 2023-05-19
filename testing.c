#include "shell.h"

/**
 * propmt - print shell prompt
 *
 * Return: void
 */
void prompt(void)
{
	char *prompt = "($) ";
	ssize_t write_c;

	if (isatty(STDIN_FILENO))
	{
		write_c = _puts(prompt);

		if (write_c == -1)
			exit(0);
	}
}



int main(void)
{
  char *line = NULL;
	char **tokens = NULL;
	int exe_st, wstatus;
	size_t line_len = 0;
	ssize_t getline_ret;
	pid_t cpid;


	/**char *cmd[] = {"/bin/ls", "-l", NULL};*/
	printf("Path =%s\n", _getenv("PATH"));
	_setenv("new", "new value", 0);
	printf("Path =%s\n", _getenv("new"));
	while (1)
	{
		line = NULL;
		tokens = NULL;
		line_len = 0;
		
		prompt();
		
		getline_ret = _getline(&line, &line_len, stdin);
		if (getline_ret == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		tokens = tokenizing(line);
	
		cpid = fork();
		if (cpid == 0)
		{
			/*printf("exexuting... (cpid =%i)\n", cpid);*/
			exe_st = execve(tokens[0], tokens, NULL);
			if (exe_st == -1)
			{
				perror("Executing Error");
				exit(0);
			}
		}
		else
		{
			wait(&wstatus);
			/*printf("Done %i : %i (cpid =%i)\n", exe_st, wstatus, cpid);*/
		}


		free(tokens);
		free(line);
		if (!isatty(STDIN_FILENO))
			break;
	}
	return (0);	
}
