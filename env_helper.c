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
		     (environ[i][var_len] == '=') )
		{
			return (environ[i] + var_len + 1);
		}
		i++;
	}

	return (NULL);
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
	int name_len, value_len;
	char *new_variable = NULL;

	if (overwrite == 0 and _getenv(name) != NULL)
		return (0);

	new_variable = malloc((name_len + value_len + 2) * sizeof(char));
	if (new_variable == NULL)
		return (-1);

	memcpy()
		
	
}
