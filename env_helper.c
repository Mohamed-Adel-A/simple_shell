#include "shell.h"
#include <unistd.h>

/**
 * _getenv - get the value of env valiable
 * @name: name of enviroment variable to be checked
 *
 */
char *_getenv(char *variable_name)
{
	int i = 0;
	int var_len;

	if (variable_name == NULL)
		return (NULL);

	var_len = _strlen(variable_name);
	while (environ[i] != NULL)
	{
		if ((_strncmp(variable_name, environ[i], var_len) == 0) &&
		     (environ[i][var_len] == '='))
		{
			return (environ[i] + var_len + 1);
		}
		i++;
	}

	return (NULL);
}

/**
 * _memcpy - copy n bytes of memory from src to dest
 * @dest: pointer to destination
 * @src: pointer to source
 * @n: number of bytes to be copied
 *
 * Return: pointer to destination
 */
void *_memcpy(void *dest, void *src, size_t n)
{
	char *d = dest, *s = src;
	size_t i = 0;

	if (src == NULL || n == 0)
		return (dest);

	if (dest == NULL)
		return (NULL);

	for (i = 0 ; i < n ; i++)
		d[i] = s[i];

	return dest;
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
	int name_len, value_len, i = 0;
	char *new_variable = NULL, *equal_sign = "=";

	if (overwrite == 0 and _getenv(name) != NULL)
		return (0);

	new_variable = malloc((name_len + value_len + 2) * sizeof(char));
	if (new_variable == NULL)
		return (-1);

	_memcpy(new_variable, name, name_len);
	_memcpy((new_variable + name_len), equal_sign, 1);
	_memcpy((new_variable + name_len + 1), value, value_len);
	new_variable[name_len + value_len + 1] = '\0';

	while (environ[i] != NULL)
	{
		if ((_strncmp(name, environ[i], name_len) == 0) &&
		     (environ[i][var_len] == '='))
		{
			free(environ[i]);
			environ[i] = new_variable;
			return (0);
		}
		i++;
	}
	return (0);
}
