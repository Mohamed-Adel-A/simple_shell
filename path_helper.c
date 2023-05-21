#include "shell"
/*
char *check_paths(char *cmd)
{
	char *all_paths;
	char *paths_array, *single_path;
	int i = 0, cmd_len, path_len;

	cmd_len = _strlen(cmd);
	all_paths = _strdup(_getenv("PATH"));
	paths_array = tokenizing(all_paths, ":");

	for (i = 0 ; paths_array[i] != NULL ; i++)
	{
		path_len = _strlen(paths_array[i]);
		single_path = malloc(sizeof(char) * (path_len + cmd_len + 1));
		_memcpy(single_path, paths_array[i], path_len);
		_memcpy(single_path + path_len, cmd, cmd_len);
		single_path[path_len + cmd_len] = '\0'; 
		printf("&s\n", single_path);
	}

	free(all_paths);
	free(paths_array);

	return (single_path);	
}
*/
