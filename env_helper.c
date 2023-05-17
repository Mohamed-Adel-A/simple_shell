#include "shell.h"

/**
 * _getenv - get the value of env valiable
 * @name: name of enviroment variable to be checked
 *
 */
char *_getenv(const char *variable_name)
{
	int i = 0;
	int var_len;

	if (name == NULL)
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
