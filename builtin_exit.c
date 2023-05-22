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
			printf("is number\n");
			errno = EINVAL;
			return (-1);
		}

		printf("s: %s : %i\n", exit_st_str, _isnumber(exit_st_str));
		exit_st_int = _atoi(exit_st_str);
		printf("i: %i\n", exit_st_int);
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



