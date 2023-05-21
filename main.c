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

/**
 * 
 */
 int check_empty_line(const char *line)
 {
	 int i = 0;
	 while (line[i] != '\0')
	 {
		 if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			 return (0);
		 i++;
	 }
	 return (1);
 }

int main(int argc , char **argv)
{
	char *line = NULL;
	char **tokens = NULL;
	int exe_st, wstatus;
	size_t line_len = 0;
	ssize_t getline_ret;
	pid_t cpid;
	char *cmd_path = NULL;

	(void)argc;
	/**char *cmd[] = {"/bin/ls", "-l", NULL};*/
	environ = create_env();
	printf("Path =%s\n", _getenv("PATH"));
	_setenv("new var", "new value", 1);
	printf("Path =%s\n", _getenv("new var"));
	print_env();
	_unsetenv("LS_COLORS");
	print_env();
	
	cmd_path = check_paths("GoCmd");

	
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
			free_env();
			exit(EXIT_SUCCESS);
		}
		else if (check_empty_line(line))
		{
			free(line);
			continue;
		}
		tokens = tokenizing(line, " \n");
	
		if (program_search(tokens[0]))
		{
			printf("start\n");
			cpid = fork();
			if (cpid == 0)
			{
				/*printf("exexuting... (cpid =%i)\n", cpid);*/
				exe_st = execve(tokens[0], tokens, NULL);
				if (exe_st == -1)
				{
					perror(argv[0]);
					exit(0);
				}
			}
			else
			{
				wait(&wstatus);
				/*printf("Done %i : %i (cpid =%i)\n", exe_st, wstatus, cpid);*/
			}
		}
		else
		{
			/*printf("else: \n");*/
			errno = ENOENT;
			perror(argv[0]);
		}

		free(tokens);
		free(line);
		
		if (!isatty(STDIN_FILENO))
			break;
	}

	free_env();
	return (0);	
}
