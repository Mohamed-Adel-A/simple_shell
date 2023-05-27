#include "shell.h"


builtin_alias(shell_data_t *sh_data)
{
	int i, eq_i = -1;
	char *tokens = sh_data->tokens;

	if (tokens[1] == NULL)
	{
		print_aliases(sh_data);
		return (0);
	}

	for(i = 0; tokens[i] != NULL; i++)
	{
		 eq_i = _strchar(tokens[i], '=');
		if (eq_i != -1)
		{
			add_alias(sh_data, tokens[i], eq_i);
		}
	}
}


int add_alias(shell_data *sh_data, char *token, int name_len)
{
	int value_len;
	char *name, *value, ret_value;
	aliases_t *aliases = sh_data->aliases, *exist_alias, *new_aliases;

	name = malloc(sizeof(char) * (name_len + 1));
	_strncpy(name, token, name_len);

	value_len = _strlen(token) - (name_len + 1);
	value = malloc(sizeof(char) * (value_len + 1));
	_strncpy(value, token + name_len + 1, value_len);

	exist_alias = get_alias(sh_data, name);
	if (exist_alias != NULL)
	{
		free(name);
		free(exist_alias->value);
		exist_alias->value = value;
		return (0);
	}

	if(aliases == NULL)
	{
		aliases = malloc(sizeof(aliases_t *) * 2);
		if(aliases == NULL)
		{
			free(name);
			free(value);
			return (-1);
		}
		aliases[0].name = name;
		aliases[0].value = value;
		aliases[1] = NULL;
		return (0);
	}
	else
	{
		;
	}
	return (0);
}


aliases_t *get_alias(shell_data_t *sh_data,char *name)
{
	aliases_t *aliases = sh_data->aliases;
	
	if (aliases == NULL)
		return (NULL);
	for (i = 0 ; aliases[i] != NULL ; i++)
	{
		if(_strncmp(name, aliases[i].name, _strlen(name) + 1) == 0)
		{
			return (&aliases[i]);
		}
	}

	return (NULL);
}


void print_aliases(shell_data_t *sh_data)
{
	int i;
	aliases_t *aliases = sh_data->aliases;

	if (aliases == NULL)
		return;
	for (i = 0 ; aliases[i] != NULL ; i++)
	{
		_puts(aliases[i].name);
		_puts("=");
		_puts("\'");
		_puts(aliases[i].value);
		_puts("\'");
		_puts("\n");
	}
}
