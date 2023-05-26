#include "shell.h"

/*************************************************/
void init_data(shell_data_t *sh_data);
int loop(shell_data_t *sh_data, char **argv);
void copy_tokens(shell_data_t *sh_data);
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
	int colon = -1, or = -1, and = -1, ret = 0;

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
	
	printf("s= %s\n", sh_data->line);
	colon = _strchar(sh_data->line, ';');

	or = _strchar(sh_data->line, '|');
	if( or != -1 && sh_data->line[or + 1] != '|')
		or = -1;

	and = _strchar(sh_data->line, '&');
	if( and != -1 && sh_data->line[and + 1] != '&')
		and = -1;

	printf(";= %i ; |= %i ; &= %i\n", colon, or, and);
	while (ret == 0)
	{
		if (colon != -1)
			ret = handle_semicolons(sh_data);
		else if (or != -1)
			ret = handle_logical_operators(sh_data, "||");
		else if (and != -1)
			ret =handle_logical_operators(sh_data, "&&");
		else
		{
			ret = 1;
			copy_tokens(sh_data);
		}

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


/**
 * copy_tokens - copy tokens from alltokens to tokens
 * sh_data: shell data
 *
 * Return: void
 */
void copy_tokens(shell_data_t *sh_data)
{
	int i;
	char **tokens = NULL, **alltokens = sh_data->alltokens;

	if (alltokens == NULL)
	{
		sh_data->tokens = NULL;
		return;
	}

	for (i = 0 ; alltokens[i] != NULL ; i++)
	{
	}
	
	tokens = malloc(sizeof(char *) * (i + 1));
	if (tokens == NULL)
	{
		sh_data->tokens = NULL;
		return;
	}

	for (i = 0 ; alltokens[i] != NULL ; i++)
	{
		tokens[i] = alltokens[i];
	}
	tokens[i] = NULL;

	sh_data->tokens = tokens;
}
