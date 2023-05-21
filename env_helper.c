#include "shell.h"

/***************************************************************/
char **create_env();
void free_env(void);
char *concat_name_value(const char *name, const char *value,
		       int name_len, int value_len);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
/***************************************************************/

/**
 * create_env - copy enviroment variable to new env variable
 *
 * Return: pointer to new env variable, or NULL other wise
 */
char **create_env()
{
	int i = 0;
	char **new_environ;
	char *env_var;

	while (environ[i] != NULL)
	{
		i++;
	}

	new_environ = malloc((i + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}

	for (i = 0 ; environ[i] != NULL ; i++)
	{
		env_var = malloc(sizeof(char) * (_strlen(environ[i]) + 1));
		if (env_var == NULL)
		{
			i--;
			for (; i >= 0 ; i--)
				free(new_environ[i]);
			free(new_environ);
			errno = ENOMEM;
			return (NULL);
		}
		strcpy(env_var, environ[i]);
		new_environ[i] = env_var;
	}
	new_environ[i] = NULL;

	/*free(environ);*/
	environ = new_environ;
	return (environ);
}

/**
 * free_env - free enviroment varible environ
 *
 * Return: void
 */
void free_env(void)
{
	int i;

	if (environ == NULL)
		return;

	for (i = 0 ; environ[i] != NULL ; i++)
	{
		free(environ[i]);
	}
	free(environ);
}


/**
 * concat_name_value - create name=value string
 * @name: varible name
 * @value: value
 * @name_len: name size
 * @value_len: value size
 *
 * Return: string to the "name=value" new string
 */
char *concat_name_value(const char *name, const char *value,
		       int name_len, int value_len)
{
	char *new_variable;

	new_variable = malloc((name_len + value_len + 2) * sizeof(char));
	if (new_variable == NULL)
	{
		return (NULL);
	}

	_memcpy(new_variable, name, name_len);
	new_variable[name_len] = '=';
	_memcpy((new_variable + name_len + 1), value, value_len);
	new_variable[name_len + value_len + 1] = '\0';

	return (new_variable);
}


/**
 * _setenv - adds variable to the environment
 * @name: variable name
 * @value: variable value
 * @overwrite: if nonzero -> overwrite the value
 *	       if zeor -> then don't change value
 *
 * Return: 0 on success, or -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int name_len = _strlen(name), value_len = _strlen(value), i = 0;
	char *new_variable;
	char **new_environ;

	if (name == NULL || value == NULL ||
	    name_len == 0 || _strchar(name, '=') != -1)
	{
		errno = EINVAL;
		return (-1);
	}
	if (overwrite == 0 && _getenv(name) != NULL)
		return (0);

	new_variable = concat_name_value(name, value, name_len, value_len);
	if (new_variable == NULL)
	{
		errno = ENOMEM;
		return (-1);
	}
	for (i = 0 ; environ[i] != NULL ; i++)
	{
		if ((_strncmp(name, environ[i], name_len) == 0) &&
		     (environ[i][name_len] == '='))
		{
			free(environ[i]);
			environ[i] = new_variable;
			return (0);
		}
	}

	new_environ = (char **) _realloc(environ, ((i + 2) * sizeof(char *)));
	if (new_environ == NULL)
	{
		errno = ENOMEM;
		return (-1);
	}
	new_environ[i] = new_variable;
	new_environ[i + 1] = NULL;
	environ = new_environ;
	return (0);
}


/**
 * _unsetenv - remove variable from the environment
 * @name: variable name
 *
 * Return: 0 on success, or -1 on error
 */
int _unsetenv(const char *name)
{
	int i = 0, var_pos = -1, name_len;

	name_len = _strlen(name);
	if (name == NULL || name_len == 0 || _strchar(name, '=') != -1)
	{
		errno = EINVAL;
		return (-1);
	}

	for (i = 0 ; environ[i] != NULL ; i++)
	{
		if ((_strncmp(name, environ[i], name_len) == 0) &&
		     (environ[i][name_len] == '='))
		{
			free(environ[i]);
			var_pos = i;
			break;
		}
	}

	if (var_pos == -1)
	{
		return (0);
	}

	for (; environ[i] != NULL ; i++)
	{
		environ[i] = environ[i + 1];
	}

	return (0);
}
