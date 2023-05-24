#include "shell.h"

int check_variable(char *str, shell_data_t *sh_data)
{
	int i = 0, var_pos, var_len, str_len, full_len;
	char *var_str, number[20], *full_string;

	if((var_pos = _strchar(token, '$')) != 0)
	{
		i = var_pos + 1;
		if (str[i] >= 'a', str[i] == )
		if(var[i] == '$')
		{
			var_str = _itoa(getpid(), number);
		}
		else if (var[1] == '?')
		{
		}
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
	int i = 0;

	if (sh_data->tokens == NULL)
		return (-1);

	token = sh_data->tokens[i];
	while (token != NULL)
	{
		if(_strchar(token, '$') != 0)
		{
			
		}
		token = sh_data->tokens[i];
		i++;
	}
}
