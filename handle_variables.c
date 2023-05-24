#include "shell.h"

/**
 * _isalpha - check if c is an alphabet
 * @c: character to be checked
 *
 * Return: 1 if it is, 0 otherwise
 */
int _isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/**
 * _isdigit - check if c is a digit
 * @c: character to be checked
 *
 * Return: 1 if it is, 0 otherwise
 */
int _isdigit(char c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}


int check_variable(int token_idx, shell_data_t *sh_data)
{
	int i = 0, var_pos, var_len, str_len, full_len, var_name_len;
	char *var_str, number[20], *full_str, *var_name = NULL, *str;
	
	str = sh_data->tokens[token_idx];
	

	while (str[i] != '\0')
	{
		var_pos = _strchar(str, '$');
		if (var_pos == -1)
			return (0);
		i = var_pos + 1;
		if(str[i] == '$')
		{
			var_str = _itoa(getpid(), number);
			i++;
			printf("$$ = %s\n", number);

		}
		else if (str[1] == '?')
		{
			var_str = _itoa(sh_data->wstatus, number);
			i++;
		}
		else
		{
			if (_isalpha(str[i]) || str[i] == '_')
			{
				while (_isalpha(str[i]) || _isdigit(str[i]) || str[i] == '_' )
				{
					i++;
				}
				var_name_len = (i - var_pos - 1);
				var_name = malloc(sizeof(char) * (var_name_len + 1));
				if (var_name == NULL)
					return (-1);
				var_name = _strncpy(var_name, str + var_pos + 1, var_name_len);
				var_str = _getenv(var_name);
				if (var_str == NULL)
				{
					return (0);
				}
			}
			else
			{
				return (0);
			}
		}	

		var_len = strlen(var_str);
		str_len = strlen(str) - (i - var_pos);
		full_len = str_len + var_len + 1;

		full_str = malloc(full_len + 1);

		memcpy(full_str, str, var_pos);
		memcpy(full_str + var_pos, var_str, var_len);
		strcpy(full_str + var_pos + var_len, str + i);

		sh_data->tokens[token_idx] = full_str;
		free(var_name);
	}
	return (0);
}


/*
int check_variable(char *str)
{
	int i = 0, var_pos, var_len, str_len, full_len;
	char *var_str, number[20], *full_str;

	if((var_pos = _strchar(str, '$')) != -1)
	{
	    i = var_pos + 1;
		if(str[i] == '$')
		{
			var_str = _itoa(getpid(), number);
			var_len = strlen(var_str);
			printf("%s\n", var_str);
			}
		else if (str[i] == '?')
		{
		}
		str_len = strlen(str) - (i - var_pos + 1);
		full_len = str_len + var_len;
		full_str = malloc(full_len + 1);
		
		memcpy(full_str, str, var_pos);
		memcpy(full_str + var_pos, var_str, var_len);
		strcpy(full_str + var_pos + var_len, str + i + 1);
		
		printf("varpos = %i, i = %i\n", var_pos, i);
		printf("varpos = %i, var_len = %i\n", var_pos, var_len);
		printf("str_len = %i, full_len = %i\n", str_len, full_len);
		printf("%s\n", full_str);
	}
	return (0);
}
*/

int handle_variables(shell_data_t *sh_data)
{
	int i = 0, check_ret;
	char *token;

	if (sh_data->tokens == NULL)
		return (-1);

	token = sh_data->tokens[i];
	while (token != NULL)
	{
		if(_strchar(token, '$') != 0)
		{
			check_ret = check_variable(i, sh_data);
			if (check_ret == -1)
				return (-1);
		}
		token = sh_data->tokens[i];
		i++;
	}
	return (0);
}
