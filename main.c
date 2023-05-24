#include "shell.h"

/**
 * prompt - print shell prompt
 *
 * Return: void
 */
void prompt(void)
{
	char *prompt = "#cisfun$ ";
	ssize_t write_c;

	if (isatty(STDIN_FILENO))
	{
		write_c = write(STDOUT_FILENO, prompt, _strlen(prompt));

		if (write_c == -1)
			exit(0);
	}
}


/**
 * free_all - free all variables
 * @sh_data: shell data
 *
 * Return: void
 */
void free_all(shell_data_t *sh_data)
{
	free(sh_data->line);
	free(sh_data->tokens);
	free(sh_data->cmd_path);
	free_variables(sh_data);
	free_env();
}



/**
 * check_cmd - check cmd for builtin and path
 * @sh_data: shell data
 * @argv: argv
 *
 * Return: 0 in success, -1 in failure
 */
int check_cmd(shell_data_t *sh_data, char **argv)
{
	int (*builtin_func)(shell_data_t *);

	sh_data->cmd_entered = sh_data->tokens[0];

	if (_strncmp(sh_data->tokens[0], "/", 1) != 0 &&
	    _strncmp(sh_data->tokens[0], "./", 2) != 0 &&
	    _strncmp(sh_data->tokens[0], "../", 3) != 0)
	{
		builtin_func = check_builtin(sh_data->tokens[0]);
		if (builtin_func != NULL)
		{
			if (builtin_func(sh_data) == -1)
			{
				errno = 127;
				perror(sh_data->tokens[0]);
			}
			free(sh_data->tokens);
			free(sh_data->line);
			free(sh_data->cmd_path);
			return (-1);
		}
		else
		{
			sh_data->cmd_path = check_paths(sh_data->tokens[0]);
			if (sh_data->cmd_path != NULL)
			{
				sh_data->tokens[0] = sh_data->cmd_path;
			}
			else
			{
				errno = 127;
				perror(argv[0]);
				return (-1);
			}
		}
	}
	return (0);
}

/**
 * excuting_cmd - executing shell commands
 * @sh_data: shell data
 * @argv: argv
 *
 * Return: 0 in success, -1 in faliure
 */
void excuting_cmd(shell_data_t *sh_data, char **argv)
{
	int exe_st;
	pid_t cpid;

	exe_st = 0;

	if (access(sh_data->tokens[0], F_OK | X_OK) == 0)
	{
		cpid = fork();
		if (cpid == 0)
		{
			signal(SIGINT, SIG_DFL);
			exe_st = execve(sh_data->tokens[0], sh_data->tokens, environ);
			if (exe_st == -1)
			{
				/*perror(sh_data->cmd_entered);*/
				perror(argv[0]);
				exit(0);
			}
		}
		else
		{
			waitpid(cpid, &(sh_data->wstatus), WUNTRACED);
		}
	}
	else
	{
		perror(argv[0]);
	}
}


/**
 * init_data - intializing shell data
 * @sh_data: shell data
 *
 * Return: void
 */
void init_data(shell_data_t *sh_data)
{
	sh_data->line = NULL;
	sh_data->tokens = NULL;
	sh_data->variables = NULL;
	sh_data->cmd_path = NULL;
	sh_data->cmd_entered = NULL;
	errno = 0;
}


/**
 * main - main function
 * @argc: argc
 * @argv: argv
 *
 * Return: 0 in success, non-zero otherwise
 */
int main(int argc, char **argv)
{
	shell_data_t sh_data;
	(void)argc;

	signal(SIGINT, handle_signal);
	/* intializing enviroment variables */
	environ = create_env();
	sh_data.wstatus = 0;
	while (1)
	{
		prompt();
		init_data(&sh_data);
		/* getting the line and handling it */
		if (getting_line(&sh_data) == -1)
		{
			sh_data.wstatus = errno;
			continue;
		}
		if (handle_variables(&sh_data) == -1)
		{
			free(sh_data.line);
			free(sh_data.tokens);
			free_variables(&sh_data);
			perror("variable error");
			sh_data.wstatus = errno;
			continue;
		}

		/* check cmd and builtins and then PATH*/
		if (check_cmd(&sh_data, argv) == -1)
		{
			sh_data.wstatus = errno;
			continue;
		}

		/*execute*/
		excuting_cmd(&sh_data, argv);

		free(sh_data.tokens);
		free_variables(&sh_data);
		free(sh_data.line);
		free(sh_data.cmd_path);

		if (!isatty(STDIN_FILENO))
			break;
	}

	printf("erron = %i\n", errno);
	free_env();
	return (errno);
}
