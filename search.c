#include "shell.h"

/**
 * str_start_with - chaech if string start wiht other string
 * @str: string to be checked
 * @start_str: string to check if str start with it
 *
 * Return: 1 if str start with start_str, 0 otherwise
 */
int str_start_with(const char *str, const char *start_str)
{
	int i = 0;
	if (str == NULL || start_str == NULL)
		return (0);
	for (i = 0; start_str[i] != '\0' ; i++)
	{
		if (start_str[i] != str[i])
			return (0);
	}

	return (1);
}

char * extract_path(const char *str)
{
	int slash_pos = -1, i = 0;

	if (!(str_start_with(str, "./")) || !(str_start_with(str, "/")))
	{
		return (NULL);
	}

	for (i = 0 ; str[i] != '\0' ; i++)
	{
		if (str[i] = '/')
			slash_pos = i;
	}
	if (slash_pos == -1)
		return (NULL)
	_str
	
}



int program_search(const char *prog)
{
	int start;

	if (str_start_with(prog, "./"))
	{
		
	}
}
