#include "shell.h"

/******************************************************/
int builtin_exit(shell_data_t *sh_data);
int builtin_cd(shell_data_t *sh_data);
int change_dir(char *olddir, char *newdir);
/******************************************************/


/**
 * builtin_exit - builtin function associated with exit cmd
 * @sh_data: arguments
 *
 * Return: 0 if success, -1 in case of failure
 */
int builtin_exit(shell_data_t *sh_data)
{
	char **args = sh_data->tokens;
	char *exit_st_str = args[1];
	int exit_st_int = 0;

	if (exit_st_str != NULL)
	{
		free_all(sh_data);
		exit(0);
	}
	else
	{
		if (args[2] != NULL)
		{
			errno = EINVAL;
			return (-1);
		}

		if (_isnumber(exit_st_str) == 0)
		{
			errno = EINVAL;
			return (-1);
		}

		exit_st_int = _atoi(exit_st_str);

		if (exit_st_int < 0)
		{
			errno = EINVAL;
			return (-1);
		}
		else if (exit_st_int > 255)
		{
			exit_st_int = exit_st_int % 256;
		}

		free_all(sh_data);
		exit(exit_st_int);
	}
}


/**
 * builtin_cd - builtin function associated with cd cmd
 * @sh_data: arguments
 *
 * Return: 0 if success, -1 in case of failure
 */
int builtin_cd(shell_data_t *sh_data)
{
	char **args = sh_data->tokens;

	/* cd (without any arguments) */
	if (args[1] == NULL)
	{
		return (change_dir(_getenv("PWD"), _getenv("HOME")));
	}

	if (args[2] != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	/* cd - */
	if (_strncmp(args[1], "-", 2) == 0)
	{
		return (change_dir(_getenv("PWD"), _getenv("OLDPWD")));
	}

	/* cd [dir] */
	return (change_dir(_getenv("PWD"), args[1]));
}

/**
 * change_dir - change current working dir and env variables
 * @olddir: current directory before change
 * @newdir: new directory to change wd to
 *
 * Return: 0 in success, -1 in failure
 */
int change_dir(char *olddir, char *newdir)
{
	char *old = NULL, *new = NULL;

	if (chdir(newdir) == -1)
	{
		return (-1);
	}

	old = _strdup(olddir);

	new = NULL;
	new = getcwd(new, PATH_MAX);

	_setenv("OLDPWD", old, 1);
	_setenv("PWD", new, 1);

	free(old);
	free(new);
	return (0);
}
