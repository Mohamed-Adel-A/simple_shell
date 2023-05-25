#include "shell.h"

int handle_semicolons(shell_data_t *sh_data)
{
	char **tokens = sh_data->alltokens, **current_tokens;
	int i, colon_pos = -1, tokens_size, index;

	index = sh_data->next_tokens_index;
	if (index == -1)
	{
		return (1);
	}
	for (i = index; tokens[i] != NULL; i++)
	{
		printf(" =%s",tokens[i]);
		if(_strncmp(tokens[i], ";", 2) == 0)
		{
			break;
		}
	}
	colon_pos = i;
	printf("\n colon_pos = %i\n", colon_pos);
	if (i == sh_data->next_tokens_index && tokens[i] != NULL)
	{
		sh_data->next_tokens_index++;
		return (0);
	}
	
	tokens_size = i - sh_data->next_tokens_index;
	printf("tokens size = %i\n", tokens_size);
	current_tokens = malloc(sizeof(char *) * (tokens_size + 1));
	if (current_tokens == NULL)
		return (-1);

	for (i = 0; i < tokens_size; i++)
	{
		current_tokens[i] = tokens[index + i];
		printf(" >%s ",current_tokens[i]);
	}
		current_tokens[i] = NULL;

	if (sh_data->tokens != NULL)
		free(sh_data->tokens);
	sh_data->tokens = current_tokens;
	printf("\n tokens[colon_pos] = %s\n",tokens[colon_pos]);

	if (tokens[colon_pos] == NULL)	
	{
		sh_data->next_tokens_index = -1;
	}
	else
		sh_data->next_tokens_index = colon_pos + 1;
	printf("index = %i\n", sh_data->next_tokens_index);
	return (0);
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
	free(sh_data->alltokens);
	free(sh_data->tokens);
	free_variables(sh_data);
}


int loop(shell_data_t *sh_data, char **argv)
{
	prompt();
	init_data(sh_data);
	if (getting_line(sh_data) == -1)
	{
		sh_data->wstatus = errno;
		return (1);
	}
	if (handle_variables(sh_data) == -1)
	{
		free_loop(sh_data);
		perror("variable error");
		sh_data->wstatus = errno;
		return (1);
	}

	while(handle_semicolons(sh_data) == 0)
	{
		
		if (check_cmd(sh_data, argv) == -1)
		{
			sh_data->wstatus = errno;
			continue;
		}

		excuting_cmd(sh_data, argv);
		free(sh_data->cmd_path);
		sh_data->cmd_path = NULL;
	}

	free_loop(sh_data);
	return (0);
}
