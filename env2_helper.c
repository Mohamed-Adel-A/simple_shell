#include "shell.h"

/*****************************************/
void print_env(void);
char *_getenv(const char *variable_name);
/*****************************************/

/**
 * buitin_en - the fuction associated with env cmd
 * @args: the arguments of the command
 *
 * Return: 0 if success, -1 if failed
 */
int builtin_env(char *arg)
{
	if (arg != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	print_env();
	return (0);
}


/**
 * print_env - print all enviroment variables
 *
 * Return: void
 */
void print_env(void)
{
	int i;

	if (environ == NULL)
		return;

	for (i = 0 ; environ[i] != NULL ; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}
}


/**
 * _getenv - get the value of env valiable
 * @variable_name: name of enviroment variable to be checked
 *
 * Return: poiter to the variable
 */
char *_getenv(const char *variable_name)
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
