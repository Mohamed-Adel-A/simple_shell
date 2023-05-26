#include "shell.h"

/*************************************************************/
void prompt(void);
int check_cmd(shell_data_t *sh_data);
void excuting_cmd(shell_data_t *sh_data, char **argv);
/*************************************************************/

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
 * check_cmd - check cmd for builtin and path
 * @sh_data: shell data
 * @argv: argv
 *
 * Return: 0 in success, -1 in failure
 */
int check_cmd(shell_data_t *sh_data)
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
				/*perror(sh_data->tokens[0]);*/
				sh_data->wstatus = 2;
			}
			free(sh_data->cmd_path);
			sh_data->cmd_path = NULL;
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
				sh_data->wstatus = 127;
				create_error(sh_data, "not found", 0, 0);
				/*perror(argv[0]);*/
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
			if (WIFEXITED(sh_data->wstatus))
				sh_data->wstatus = WEXITSTATUS(sh_data->wstatus);
			else
				sh_data->wstatus = 0;
			/*printf("ws= %i\n", sh_data->wstatus);*/
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
	int loop_ret;
	int fd;

	(void)argc;
	signal(SIGINT, handle_signal);
	environ = create_env();
	sh_data.wstatus = 0;
	sh_data.cmd_idx = 0;
	sh_data.argv = argv;
	if (argc != 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			/* ./hsh: 0: Can't open /tmp/hbtn_checker_tmp_27147 * 127 */
			create_error(&sh_data, "Can't open ", 0, 1);
			/*close(fd);*/
			exit(-1);
		}

		sh_data.fd = fd;
	}
	else
		sh_data.fd = STDIN_FILENO;

	while (1)
	{
		loop_ret = loop(&sh_data, argv);
		if (loop_ret == 1)
			continue;
	}

	colse_file(&sh_data);
	free_env();
	return (errno);
}
