#include "shell.h"

/***********************************************************/
void free_variables(shell_data_t *sh_data);
int add_variable(char *var, shell_data_t *sh_data);
int check_variable(int token_idx, shell_data_t *sh_data);
int handle_variables(shell_data_t *sh_data);
/***********************************************************/



/**
 * free_variables - free varibles from sh_data->variables
 * @sh_data: shell data
 *
 * Return: void
 */
void free_variables(shell_data_t *sh_data)
{
	int i;

	if (sh_data->variables == NULL)
	{
		return;
	}
	else
	{
		for (i = 0 ; sh_data->variables[i] != NULL ; i++)
		{
			free(sh_data->variables[i]);
		}
		free(sh_data->variables);
	}
}


/**
 * add_variable - add variable to variables list to be freed later
 * @var: pointer to variable
 * @sh_data: shell data
 *
 * Return: undesided yet
 */
int add_variable(char *var, shell_data_t *sh_data)
{
	int i = 0;
	char **old_vars, **new_vars;

	old_vars = sh_data->variables;
	if (old_vars == NULL)
	{
		new_vars = malloc(sizeof(char *) * 2);
		if (new_vars == NULL)
			return (-1);
		sh_data->variables = new_vars;
	}
	else
	{
		for (i = 0 ; old_vars[i] != NULL ; i++)
		{
		}

		new_vars = _realloc(old_vars, sizeof(char *) * (i + 3), sizeof(char *) * i);
		if (new_vars == NULL)
		{
			return (-1);
		}
	}

	new_vars[i] = var;
	new_vars[i + 1] = NULL;
	sh_data->variables = new_vars;

	return (0);
}



/**
 * check_variable - check if there is variable and replace it
 * @token_idx: index of the token that have $ in it
 * @sh_data: shell data
 *
 * Return: 0 in success, -1 in failure
 */
int check_variable(int token_idx, shell_data_t *sh_data)
{
	int i = 0, var_pos, var_len, str_len, full_len, var_name_len;
	char *var_str, number[20], *full_str, *var_name = NULL, *str;

	str = sh_data->alltokens[token_idx];
	i = 0;
	while (str[i] != '\0')
	{
		var_pos = _strchar(str + i, '$') + i;
		if (var_pos == -1)
		{
			return (0);
		}
		i = var_pos + 1;
		if (str[i] == '$')
		{
			var_str = _itoa(getpid(), number);
			i++;

		}
		else if (str[i] == '?')
		{
			var_str = _itoa(sh_data->wstatus, number);
			i++;
		}
		else
		{
			if (_isalpha(str[i]) || str[i] == '_')
			{
				while (_isalpha(str[i]) || _isdigit(str[i]) || str[i] == '_')
				{
					i++;
				}
				var_name_len = (i - var_pos - 1);
				var_name = malloc(sizeof(char) * (var_name_len + 1));
				if (var_name == NULL)
					return (-1);
				var_name = _strncpy(var_name, str + var_pos + 1, var_name_len);
				var_str = _getenv(var_name);
				free(var_name);
				if (var_str == NULL)
				{
					continue;
				}
			}
			else
			{
				i++;
				continue;
			}
		}

		var_len = strlen(var_str);
		str_len = strlen(str) - (i - var_pos);
		full_len = str_len + var_len + 1;
		printf("var_len= %i ; str_len= %i ;  full_len= %i \n", var_len, str_len, full_len);

		full_str = malloc(full_len + 1);
		
		
		printf("s[%i] = %c --\n", i, str[i]);

		memcpy(full_str, str, var_pos);
		memcpy(full_str + var_pos, var_str, var_len);
		strcpy(full_str + var_pos + var_len, str + i);
		printf("full: %s\n", full_str);

		free(sh_data->alltokens[token_idx]);
		sh_data->alltokens[token_idx] = full_str;
		str = sh_data->alltokens[token_idx];
		add_variable(full_str, sh_data);
		if (str[i] == '\0')
			break;
	}
	return (0);
}



/**
 * handle_variables - function that handel variables
 * @sh_data: shell data
 *
 * Return: 0 in success, -1 in failure
 */
int handle_variables(shell_data_t *sh_data)
{
	int i = 0, check_ret;
	char *token;

	if (sh_data->alltokens == NULL)
		return (-1);

	token = sh_data->alltokens[i];
	while (token != NULL)
	{
		if (_strchar(token, '$') != -1)
		{
			check_ret = check_variable(i, sh_data);
			if (check_ret == -1)
				return (-1);
		}
		i++;
		token = sh_data->alltokens[i];
	}
	return (0);
}
