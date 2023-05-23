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

typedef struct shell_data
{
	char *line;
	char **tokens;
	int wstatus;
	char *cmd_path;
	unsigned int cmd_index;
} shell_data_t;

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
 * getting_line - get line via getline and then check the line
 * @sh_data: shell data
 *
 * Return: 0 in success, -1 in failure
 */
int getting_line(shell_data_t *sh_data)
{
	ssize_t getline_ret;
	size_t line_len = 0;
	char *line = NULL;

	getline_ret = _getline(&line, &line_len, stdin);
	if (getline_ret == -1)
	{
		free_all(sh_data);
		_puts("\n");
		exit(EXIT_SUCCESS);
	}
	else if (check_empty_line(line))
	{
		free(line);
		return (-1);
	}

	handle_comments(line);
	sh_data->line = line;
	sh_data->tokens = tokenizing(line, " \n");
	return (0);
}



int main(int argc , char **argv)
{
	/*
	char *line = NULL;
	char **tokens = NULL;
	size_t line_len = 0;
	char *cmd_path = NULL;
	*/
	
	int exe_st;
	pid_t cpid;
	int (*builtin_func)(char **);
	shell_data_t sh_data;

	(void)argc;
	/**char *cmd[] = {"/bin/ls", "-l", NULL};*/
	
	/* intializing enviroment variables */
	environ = create_env();	
	
	while (1)
	{
		sh_data.line = NULL;
		sh_data.tokens = NULL;
		sh_data.cmd_path = NULL;
		exe_st = 0;
		
		/*
		line = NULL;
		tokens = NULL;
		line_len = 0;
		cmd_path = NULL;
		exe_st = 0;
		*/
		
		prompt();
		/* getting the line and handling it */
		if (getting_line(&sh_data) == -1)
			continue;
		/*
		getline_ret = _getline(&line, &line_len, stdin);
		if (getline_ret == -1)
		{
			free(line);
			free_env();
			_puts("\n");
			exit(EXIT_SUCCESS);
		}
		else if (check_empty_line(line))
		{
			free(line);
			continue;
		}
		handle_comments(line);
		tokens = tokenizing(line, " \n");
		*/

		/* check cmd and builtins and then PATH*/
		if(_strncmp(sh_data.tokens[0], "/", 1) != 0 && _strncmp(sh_data.tokens[0], "./", 2) != 0 &&
		  _strncmp(sh_data.tokens[0], "../", 3) != 0)
		{
			builtin_func = check_builtin(sh_data.tokens[0]);
			if (builtin_func != NULL)
			{
				if(builtin_func(sh_data.tokens) == -1)
				{
					perror(sh_data.tokens[0]);
				}
				free(sh_data.tokens);
				free(sh_data.line);
				free(sh_data.cmd_path);
				continue;
			}
			else
			{
				sh_data.cmd_path = check_paths(sh_data.tokens[0]);
				if (sh_data.cmd_path != NULL)
					sh_data.tokens[0] = sh_data.cmd_path;
			}
		}
		
		
		/*execute*/
		if (access(sh_data.tokens[0], F_OK | X_OK) == 0)
		{
			/*printf("start\n");*/
			cpid = fork();
			if (cpid == 0)
			{
				/*printf("exexuting... (cpid =%i)\n", cpid);*/
				exe_st = execve(sh_data.tokens[0], sh_data.tokens, environ);
				if (exe_st == -1)
				{
					perror(argv[0]);
					exit(0);
				}
			}
			else
			{
				wait(&(sh_data.wstatus));
				printf("Done %i : %i (cpid =%i)\n", exe_st, sh_data.wstatus, cpid);
			}
		}
		else
		{
			/*printf("else: \n");*/
			/*errno = ENOENT;*/
			perror(argv[0]);
		}

		free(sh_data.tokens);
		free(sh_data.line);
		free(sh_data.cmd_path);
		
		if (!isatty(STDIN_FILENO))
			break;
	}

	free_env();
	return (0);	
}
