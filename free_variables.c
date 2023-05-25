#include "shell.h"

/*******************************************************/
void free_loop(shell_data_t *sh_data);
void free_tokens(shell_data_t *sh_data);
void free_all(shell_data_t *sh_data);
/*******************************************************/



/**
 * free_loop - free all variables
 * @sh_data: shell data
 *
 * Return: void
 */
void free_loop(shell_data_t *sh_data)
{
	free(sh_data->line);
	free_tokens(sh_data);
	free(sh_data->tokens);
	free_variables(sh_data);
}



/**
 * free_takens - free all tokens
 * @sh_data: shell data
 *
 * Return: void
 */
void free_tokens(shell_data_t *sh_data)
{
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
}
