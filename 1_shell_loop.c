#include "shell.h"

/*************************************************/
void init_data(shell_data_t *sh_data);
int loop(shell_data_t *sh_data, char **argv);
/*************************************************/

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
	sh_data->alltokens = NULL;
	sh_data->variables = NULL;
	sh_data->cmd_path = NULL;
	sh_data->cmd_entered = NULL;
	sh_data->next_tokens_index = 0;
	sh_data->cmd_idx++;
	errno = 0;
}


/**
 * loop - the contents of the shell loop
 * @sh_data: shell data
 * @argv: argv
 *
 * Return: 1 loop, 0 same as 1
 */
int loop(shell_data_t *sh_data, char **argv)
{
	prompt();
	init_data(sh_data);
	if (getting_line(sh_data) == -1)
	{
		/*sh_data->wstatus = errno;*/
		return (1);
	}
	if (handle_variables(sh_data) == -1)
	{
		free_loop(sh_data);
		perror("variable error");
		/*sh_data->wstatus = errno;*/
		return (1);
	}

	while (handle_semicolons(sh_data) == 0)
	{
		if (check_cmd(sh_data) == -1)
		{
			/*sh_data->wstatus = -1;*/
			continue;
		}

		excuting_cmd(sh_data, argv);
		free(sh_data->cmd_path);
		sh_data->cmd_path = NULL;
	}

	free_loop(sh_data);
	return (0);
}
