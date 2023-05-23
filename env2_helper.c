#include "shell.h"

/*****************************************/
int builtin_setenv(shell_data_t *sh_data);
int builtin_unsetenv(shell_data_t *sh_data);
int builtin_env(shell_data_t *sh_data);
void print_env(void);
char *_getenv(const char *variable_name);
/*****************************************/

/**
 * builtin_setenv - builtin function associated with setenv cmd
 * @args: arguments
 *
 * Return: 0 if success, -1 in failure
 */
int builtin_setenv(shell_data_t *sh_data)
{
	char **args = sh_data->tokens;
	int setenv_ret;

	if (args[3] != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	setenv_ret = _setenv(args[1], args[2], 1);
	if (setenv_ret == -1)
	{
		return (-1);
	}

	return (0);
}

/**
 * builtin_unsetenv - builtin function associated with unsetenv cmd
 * @args: arguments
 *
 * Return: 0 if success, -1 in failure
 */
int builtin_unsetenv(shell_data_t *sh_data)
{
	char **args = sh_data->tokens;
	int unsetenv_ret;

	if (args[2] != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	unsetenv_ret = _unsetenv(args[1]);
	if (unsetenv_ret == -1)
	{
		return (-1);
	}

	return (0);
}

/**
 * builtin_env - the fuction associated with env cmd
 * @args: the arguments of the command
 *
 * Return: 0 if success, -1 if failed
 */
int builtin_env(shell_data_t *sh_data)
{
	char **args = sh_data->tokens;

	if (args[1] != NULL)
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
