#include "shell.h"

/**
 * builtin_exit - builtin function associated with exit cmd
 * @args: arguments
 *
 * Return: 0 if success, -1 in case of failure
 */
int builtin_exit(char **args)
{
	char *exit_st_str = args[1];
	int exit_st_int = 0;

	if (args[2] != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	if (exit_st_str != NULL)
	{
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
	}

	/*free_vars();*/
	exit(exit_st_int);
}


/**
 *
 *
 */
int builtin_cd(char **args)
{
	int chdir_ret;
	char *home_dir, *olddir, *newdir;

	if (args[2] != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	/* cd (without any arguments) */
	if (args[1] == NULL)
	{
		home_dir = _getenv("HOME");
		chdir_ret = chdir(home_dir);

		if (chdir_ret == -1)
		{
			return (-1);
		}

		_setenv("PWD", home_dir, 1);
		return (0); 
	}

	printf("%s : %i", args[1], _strncmp(args[1], "-", 2));
	/* cd - */
	if(_strncmp(args[1], "-", 2) != 0)
	{
		newdir = _getenv("OLDPWD");
		olddir = _getenv("PWD");
		
		chdir_ret = chdir(newdir);
		if (chdir_ret == -1)
		{
			return (-1);
		}

		_setenv("PWD", newdir, 1);
		_setenv("OLDPWD", olddir, 1);
		return (0);
	}

	/* cd [dir] */
	newdir = args[1];
	olddir = _getenv("PWD");		
	chdir_ret = chdir(newdir);
	if (chdir_ret == -1)
	{
		return (-1);
	}

	_setenv("PWD", newdir, 1);
	_setenv("OLDPWD", olddir, 1);
	return (0);
}
