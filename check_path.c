#include "shell.h"

/*******************************************/
char *check_paths(char *cmd);
void free_used_paths(char **paths_array);
/*******************************************/


/**
 * check_paths - search for cmd in paths in PATH
 * @cmd: the program name
 *
 * Return: pointer to full path of the program, NULL if not found
 */
char *check_paths(char *cmd)
{
	char *all_paths, *single_path = NULL;
	char **paths_array;
	int i = 0, cmd_len, path_len;

	cmd_len = _strlen(cmd);
	all_paths = _strdup(_getenv("PATH"));
	if (all_paths == NULL)
		return (NULL);
	paths_array = tokenizing(all_paths, ":");

	for (i = 0 ; paths_array[i] != NULL ; i++)
	{
		path_len = _strlen(paths_array[i]);
		single_path = malloc(sizeof(char) * (path_len + cmd_len + 2));
		_memcpy(single_path, paths_array[i], path_len);
		single_path[path_len] = '/';
		_memcpy(single_path + path_len + 1, cmd, cmd_len);
		single_path[path_len + cmd_len + 1] = '\0';
		if (access(single_path, F_OK) == 0)
		{
			break;
		}
		free(single_path);
		single_path = NULL;
	}

	free(all_paths);
	free_used_paths(paths_array);

	return (single_path);
}


/**
 * free_used_paths - free paths used in check paths
 * @paths_array: tokenized pathed to be freed
 *
 * Return: void
 */
void free_used_paths(char **paths_array)
{
	int i;

	if (paths_array == NULL)
		return;

	for (i = 0 ; paths_array[i] != NULL ; i++)
		free(paths_array[i]);

	free(paths_array);
}
