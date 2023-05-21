#include "shell"

char *check_paths(char *cmd)
{
	char *all_paths = _strdup(_getenv("PATH"));
	char *paths_array, *single_path;
	int i = 0, cmd_len, path_len;

	cmd_len = _strlen(cmd);
	paths_array = tokenizing(all_paths, ":");

	
	for (i = 0 ; paths_array[i] != NULL ; i++)
	{
		single_path = malloc(sizeof(char) * (_strlen(paths_array[i]) + _strlen(cmd) + 1));
		_memcpy(single_path, _strlen(paths_array[i], );
		printf("&s\n", paths_array[i]);
	}
	
}
