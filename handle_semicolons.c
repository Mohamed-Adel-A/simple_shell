#include "shell.h"

int handle_semicolons(shell_data_t *sh_data)
{
	char **tokens = sh_data->alltokens, *current_tokens;
	int i, colon_pos = -1;

	i = sh_data->next_tokens_index;
	if(i == -1)
	{
		return (1);
	}
	for (i = 0 ; tokens[i] != NULL; i++)
	{
		if(_strncmp(tokens[i], ";", 2) != -1)
		{
			colon_pos = i;
			break;
		}
	}

	i = sh_data->next_tokens_index;
	current_tokens = mlloc(sizeof(*char) * i);
	if (current_tokens == NULL)
		return (-1);
	for (i = 0 ; i < colon_pos; i++)
	{
		current_tokens[i] = tokens[i];
	}
		current_tokens[i] = NULL;

	if (sh_data->tokens != NULL)
		free(sh_data->tokens);
	sh_data->tokens = current_tokens;

	if (tokens[i] != NULL)	
	{
		sh_data->next_tokens_index = -1;
	}
	sh_data->next_tokens_index = colon_pos + 1;
	return (0)
}
