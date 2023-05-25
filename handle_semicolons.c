#include "shell.h"

int handle_semicolons(shell_data_t *sh_data)
{
	char **tokens = sh_data->alltokens, *current_tokens;
	int i, colon_pos = -1, tokens_size;

	i = sh_data->next_tokens_index;
	if(i == -1)
	{
		return (1);
	}
	for (; tokens[i] != NULL; i++)
	{
		if(_strncmp(tokens[i], ";", 2) != -1)
		{
			break;
		}
	}

	if (i == sh_data->next_tokens_index && tokens[i] != NULL)
	{
		sh_data->next_tokens_index++;
		return (0);
	}
	
	tokens_size = i - sh_data->next_tokens_index;
	current_tokens = mlloc(sizeof(*char) * (tokens_size));
	if (current_tokens == NULL)
		return (-1);

	for (i = 0; i < tokens_size; i++)
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




int loop(shell_data_t *sh_data, char **argv)
{
	int tok_ret = 0;

	while(tok_ret == 0)
	{
		prompt();
		init_data(sh_data);
		if (getting_line(sh_data) == -1)
		{
			sh_data.wstatus = errno;
			return (1);
		}
		if (handle_variables(sh_data) == -1)
		{
			free_loop(sh_data);
			perror("variable error");
			sh_data->wstatus = errno;
			return (1);
		}

		tok_ret = handle_semicolons(sh_data);
		
		if (check_cmd(sh_data, argv) == -1)
		{
			sh_data->wstatus = errno;
			return (1);
		}

		excuting_cmd(sh_data, argv);
		free_loop(sh_data);
	}
}
