#include "shell.h"

int builtin_exit(char *exit_st_str)
{
	/*char *exit_st_str;*/
	int exit_st_int = 0;

	if (_isnumber(exit_st_str))
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

	/*free_vars();*/
	exit (exit_st_int);
}



