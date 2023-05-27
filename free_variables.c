#include "shell.h"

/*******************************************************/
void free_loop(shell_data_t *sh_data);
void free_tokens(shell_data_t *sh_data);
void free_all(shell_data_t *sh_data);
void colse_file(shell_data_t *sh_data);
/*******************************************************/

/**
 * free_aliases - free aliases
 * @sh_data: shell data
 *
 * Return: void
 */
void free_aliases(shell_data_t *sh_data)
{
	int i;

	if (sh_data->aliases == NULL)
		return;
	for (i = 0 ; sh_data->aliases[i] != NULL ; i++)
	{
		free(sh_data->aliases[i]->name);
		free(sh_data->aliases[i]->value);
		free(sh_data->aliases[i]);
	}
	free(sh_data->aliases);
}

/**
 * free_loop - free all variables
 * @sh_data: shell data
 *
 * Return: void
 */
void free_loop(shell_data_t *sh_data)
{
	free(sh_data->line);

	if (sh_data->tokens != sh_data->alltokens)
		free(sh_data->tokens);

	free_tokens(sh_data);
	free(sh_data->cmd_path);
	free_variables(sh_data);
}



/**
 * free_tokens - free all tokens
 * @sh_data: shell data
 *
 * Return: void
 */
void free_tokens(shell_data_t *sh_data)
{
	int i;

	if (sh_data->alltokens == NULL)
		return;

	for (i = 0 ; sh_data->alltokens[i] != NULL ; i++)
	{
		free(sh_data->alltokens[i]);
	}

	free(sh_data->alltokens);
	sh_data->alltokens = NULL;
}



/**
 * free_all - free all variables
 * @sh_data: shell data
 *
 * Return: void
 */
void free_all(shell_data_t *sh_data)
{
	free_loop(sh_data);
	free_env();
	colse_file(sh_data);
}


/**
 * colse_file - close file if open
 * @sh_data: shell data
 *
 * Return: void
 */
void colse_file(shell_data_t *sh_data)
{
	if (sh_data->fd != STDIN_FILENO)
		close(sh_data->fd);
}
