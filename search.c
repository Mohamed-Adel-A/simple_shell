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

/**
 * extract_path - extract path and filename from full path
 * @fullpath: full path containg path and filename
 * @path: extracted path
 * @filename: extracted filename
 *
 * Return: 1 if fined path and filename, 0 otherwise
 */
int extract_path(const char *str, char *path, char *file_name)
{
	int slash_pos = -1, i = 0;

	if (!(str_start_with(str, "./")) && !(str_start_with(str, "/")))
	{
		path[i] = '\0';
		return (0);
	}

	for (i = 0 ; str[i] != '\0' ; i++)
	{
		if (str[i] == '/')
			slash_pos = i;
	}
	if (slash_pos == -1)
	{
		path[0]='\0';
		return (0);
	}

	_memcpy(path, str, slash_pos + 1);
	path[slash_pos + 1]= '\0';
	if (str[slash_pos + 1] != '\0')
	{
		_strcpy(file_name, (str + slash_pos + 1));
	}
	else
	{
		file_name = NULL;
		return (0);
	}

	return (1);
}



int program_search(const char *fullpath)
{
	int start, ret_extract;
	char path[1024], file_name[265];

	if (!str_start_with(fullpath, "./") && !str_start_with(fullpath, "/"))
	{
		return (0);
	}

	ret_extract = extract_path(fullpath, path, name);
	if (ret_extract == 0)
		return (0);
	
	
	
}
