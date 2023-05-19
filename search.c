#include "shell.h"



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


/**
 * program_search - check if the program exist
 * @fullpath: full path to the program
 *
 * Return: 1 if progtam exitst, 0 otherwise
 */
int program_search(const char *fullpath)
{
	int start, ret_extract;
	char path[1024], file_name[265];
	DIR *opened_dir;
	struct dirent *dir_entry;

	if (!str_start_with(fullpath, "./") && !str_start_with(fullpath, "/"))
	{
		return (0);
	}

	ret_extract = extract_path(fullpath, path, name);
	if (ret_extract == 0)
		return (0);

	opened_dir = opendir(path);
	if (opened_dir == NULL)
		return (0);

	while ((dir_entry = readdir(opened_dir)) != NULL)
	{
		if (dir_entry->d_type == DT_REG &&
		    _strncmp(file_name,dir_entry->d_name, (_strlen(file_name) + 1)) == 0)
		{
			closedir(opened_dir);
			return (1);
		}
	}

	closedir(opened_dir);
	return (0);
}
