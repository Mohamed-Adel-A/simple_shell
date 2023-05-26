#include "shell.h"

int handle_semicolons(shell_data_t *sh_data)
{
	char **tokens = sh_data->alltokens, **current_tokens;
	int i, colon_pos = -1, tokens_size, index, diff_pos;

	index = sh_data->next_tokens_index;
	if (index == -1 || tokens[i] == NULL)
	{
		sh_data->next_tokens_index = -1;
		return (1);
	}
	for (i = index; tokens[i] != NULL; i++)
	{
		if(_strncmp(tokens[i], ";", 2) == 0)
		{
			break;
		}
	}
	colon_pos = i;
	diff_pos = i - (sh_data->next_tokens_index);
	if (diff_pos == 0  && tokens[i] != NULL)
	{
		sh_data->next_tokens_index++;
		return (0);
	}
	
	tokens_size = i - sh_data->next_tokens_index;
	current_tokens = malloc(sizeof(char *) * (tokens_size + 1));
	if (current_tokens == NULL)
		return (-1);

	for (i = 0; i < tokens_size; i++)
	{
		current_tokens[i] = tokens[index + i];
	}
		current_tokens[i] = NULL;

	if (sh_data->tokens != NULL)
		free(sh_data->tokens);
	sh_data->tokens = current_tokens;

	if (tokens[colon_pos] == NULL || tokens[colon_pos + 1] == NULL)	
	{
		sh_data->next_tokens_index = -1;
	}
	else
		sh_data->next_tokens_index = colon_pos + 1;
	return (0);
}

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

	while(handle_semicolons(sh_data) == 0)
	{
		if (check_cmd(sh_data, argv) == -1)
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
