#include "shell.h"
/**
 * simicolons_in_str - handle semicolons in middle of string
 * @sh_data: shell data
 *
 * Return: 0 success, -1 failure
 */
int simicolons_in_str(shell_data_t *sh_data)
{
	int i, j, line_len;
	char *line = sh_data->line, *new_line;

	if (line == NULL)
		return (-1);

	line_len = _strlen(line);
	for (i = 0 ; line[i] != '\0' ; i++)
	{
		if (line[i] == ';')
		{
			if (i != 0 && line[i - 1] == ' ' && line[i + 1] == ' ')
				continue;

			new_line = malloc(sizeof(char) * (line_len + 3));
			if (new_line == NULL)
				return (-1);
			for (j = 0; j < i ; j++)
				new_line[j] = line[j];
			new_line[j++] = ' ';
			new_line[j++] = ';';
			new_line[j++] = ' ';
			for (; line[j - 2] != '\0'; j++)
				new_line[j] = line[j - 2];
			new_line[j] = '\0';
			free(line);

			line = new_line;
			i += 2;
		}
	}
	sh_data->line = line;
	return (0);
}


/**
 * handle_semicolons - break tokens series on ;
 * @sh_data: shell data
 *
 * Return: 1 there is no other tokens, 0 still there
 *         -1 failure
 */
int handle_semicolons(shell_data_t *sh_data)
{
	char **tokens = sh_data->alltokens, **current_tokens;
	int i, colon_pos = -1, tokens_size, index, diff_pos;

	index = sh_data->next_tokens_index;
	if (index == -1 || tokens[index] == NULL)
	{
		sh_data->next_tokens_index = -1;
		return (1);
	}
	for (i = index; tokens[i] != NULL; i++)
	{
		if (_strncmp(tokens[i], ";", 2) == 0)
			break;
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
		current_tokens[i] = tokens[index + i];

	current_tokens[i] = NULL;

	if (sh_data->tokens != NULL)
		free(sh_data->tokens);
	sh_data->tokens = current_tokens;

	if (tokens[colon_pos] == NULL || tokens[colon_pos + 1] == NULL)
		sh_data->next_tokens_index = -1;
	else
		sh_data->next_tokens_index = colon_pos + 1;
	return (0);
}



/**
 * simicolons_in_str - handle semicolons in middle of string
 * @sh_data: shell data
 * @operator: logical operators
 *
 * Return: 0 success, -1 failure
 */
int logical_operators_in_str(shell_data_t *sh_data,char operator)
{
	int i, j, line_len;
	char *line = sh_data->line, *new_line;

	if (line == NULL)
		return (-1);

	line_len = _strlen(line);
	for (i = 0 ; line[i] != '\0' ; i++)
	{
		if (line[i] == operator && line[i + 1] == operator)
		{
			if (i != 0 && line[i - 1] == ' ' && line[i + 2] == ' ')
				continue;

			new_line = malloc(sizeof(char) * (line_len + 3));
			if (new_line == NULL)
				return (-1);
			for (j = 0; j < i ; j++)
				new_line[j] = line[j];
			new_line[j++] = ' ';
			new_line[j++] = operator;
			new_line[j++] = operator;
			new_line[j++] = ' ';
			for (; line[j - 2] != '\0'; j++)
				new_line[j] = line[j - 2];
			new_line[j] = '\0';
			free(line);

			line = new_line;
			i += 2;
		}
	}
	sh_data->line = line;
	return (0);
}


/**
 * handle_logical_operators - break tokens series on || or &&
 * @sh_data: shell data
 *
 * Return: 1 there is no other tokens, 0 still there
 *         -1 failure
 */
int handle_logical_operators(shell_data_t *sh_data)
{
	char **tokens = sh_data->alltokens, **current_tokens;
	int i, colon_pos = -1, tokens_size, index, diff_pos;

	index = sh_data->next_tokens_index;
	if (index == -1 || tokens[index] == NULL)
	{
		sh_data->next_tokens_index = -1;
		return (1);
	}
	for (i = index; tokens[i] != NULL; i++)
	{
		if (_strncmp(tokens[i], "||", 3) == 0)
		{
			sh_data->logical_op = '|';
			break;
		}
		if (_strncmp(tokens[i], "&&", 3) == 0)
		{
			sh_data->logical_op = '&';
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
		current_tokens[i] = tokens[index + i];

	current_tokens[i] = NULL;

	if (sh_data->tokens != NULL)
		free(sh_data->tokens);
	sh_data->tokens = current_tokens;

	if (tokens[colon_pos] == NULL || tokens[colon_pos + 1] == NULL)
		sh_data->next_tokens_index = -1;
	else
		sh_data->next_tokens_index = colon_pos + 1;
	return (0);
}
