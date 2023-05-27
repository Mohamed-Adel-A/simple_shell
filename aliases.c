#include "shell.h"


/**********************************************/
int builtin_alias(shell_data_t *sh_data);
void print_aliases(shell_data_t *sh_data);
int add_alias(shell_data_t *sh_data, char *token, int name_len);
aliases_t *get_alias(shell_data_t *sh_data,char *name);
void print_aliases(shell_data_t *sh_data);
/**********************************************/


/**
 * builtin_alias - builtin_alias
 * @sh_data: shell data
 *
 * Return: 0 success, -1 fail
 */
int builtin_alias(shell_data_t *sh_data)
{
	int i, eq_i = -1;
	char **tokens = sh_data->tokens;
	aliases_t *alias;

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
			continue;
		}
		alias = get_alias(sh_data, tokens[i]);
		if (alias != NULL)
		{
			_puts(alias->name);
			_puts("=");
			_puts("\'");
			_puts(alias->value);
			_puts("\'");
			_puts("\n");
		}
	}
	return (0);
}

/**
 * add_alias - get_alias
 * @sh_data: shell data
 * @token: token
 * @name_len: name_len
 *
 * Return: void
 */
int add_alias(shell_data_t *sh_data, char *token, int name_len)
{
	int i, value_len;
	char *name, *value;
	aliases_t **aliases = sh_data->aliases, *exist_alias, *new_alias;

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

	new_alias = malloc(sizeof(aliases_t));
	new_alias->name = name;
	new_alias->value = name;
	if(aliases == NULL)
	{
		aliases = malloc(sizeof(aliases_t *) * 2);
		aliases[0] =new_alias;
		aliases[1] = NULL;
		return (0);
	}
	else
	{
		for (i = 0 ; aliases[i] != NULL ; i++)
		{
		}
		aliases = _realloc(aliases, i + 2, i);
		aliases[i] = new_alias;
		aliases[i + 1] = NULL;		
	}
	return (0);
}

/**
 * get_alias - get_alias
 * @sh_data: shell data
 * @name: name
 *
 * Return: void
 */
aliases_t *get_alias(shell_data_t *sh_data,char *name)
{
	int i;
	aliases_t **aliases = sh_data->aliases;
	
	if (aliases == NULL)
		return (NULL);
	for (i = 0 ; aliases[i] != NULL ; i++)
	{
		if(_strncmp(name, aliases[i]->name, _strlen(name) + 1) == 0)
		{
			return (aliases[i]);
		}
	}

	return (NULL);
}

/**
 * print_aliases - print_aliases
 * @sh_data: shell data
 *
 * Return: void
 */
void print_aliases(shell_data_t *sh_data)
{
	int i;
	aliases_t **aliases = sh_data->aliases;

	if (aliases == NULL)
		return;
	for (i = 0 ; aliases[i] != NULL ; i++)
	{
		_puts(aliases[i]->name);
		_puts("=");
		_puts("\'");
		_puts(aliases[i]->value);
		_puts("\'");
		_puts("\n");
	}
}
