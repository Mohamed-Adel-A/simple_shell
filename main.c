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
	free_env();
}



/**
 * check_cmd - check cmd for builtin and path
 * @sh_data: shell data
 *
 * Return: 0 in success, -1 in failure
 */
int check_cmd(shell_data_t *sh_data)
{
	int (*builtin_func)(shell_data_t *);

	sh_data->cmd_entered = sh_data->tokens[0];
	sh_data->cmd_path = sh_data->tokens[0];

	if (_strncmp(sh_data->tokens[0], "/", 1) != 0 &&
	    _strncmp(sh_data->tokens[0], "./", 2) != 0 &&
	    _strncmp(sh_data->tokens[0], "../", 3) != 0)
	{
		builtin_func = check_builtin(sh_data->tokens[0]);
		if (builtin_func != NULL)
		{
			if (builtin_func(sh_data) == -1)
			{
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
			if (sh_data->cmd_path == NULL)
			{
				perror(sh_data->tokens[0]);
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
			exe_st = execve(sh_data->cmd_path, sh_data->tokens, environ);
			if (exe_st == -1)
			{
				perror(sh_data->cmd_entered);
				exit(0);
			}
		}
		else
		{
			wait(&(sh_data->wstatus));
		}
	}
	else
	{
		perror(argv[0]);
	}
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

	while (1)
	{
		sh_data.line = NULL;
		sh_data.tokens = NULL;
		sh_data.cmd_path = NULL;
		sh_data.cmd_entered = NULL;

		prompt();
		/* getting the line and handling it */
		if (getting_line(&sh_data) == -1)
			continue;

		/* check cmd and builtins and then PATH*/
		if (check_cmd(&sh_data) == -1)
			continue;

		/*execute*/
		excuting_cmd(&sh_data, argv);

		free(sh_data.tokens);
		free(sh_data.line);
		free(sh_data.cmd_path);

		if (!isatty(STDIN_FILENO))
			break;
	}

	free_env();
	return (0);
}
