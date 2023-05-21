#include "shell.h"

/**
 * struct buitins - struct contains builins names and fuctions
 * @name: string contains the command to be used to call the function
 * @funcction: pointer to the buitin function to be called
 *
 */
typedef struct buitins
{
	char *name;
	int (*function)(char *arg); 
} buitin_t;

/**
 * check_builtin - check if the command is buitlin command
 * @cmd: the command to be checked
 *
 * Return: pointer to the function to be called of NUll if not
 */
int (*check_builtin(char *cmd))(char *)
{
	int i = 0, cmd_len;
	buitin_t builtins_array[] = { {"exit", builtin_exit},
				     {"env", builtin_env},
				     {NULL, NULL}
				    };
	if (cmd == NULL)
		return (NULL);

	cmd_len = _strlen(cmd);
	for (i = 0; builtins_array[i]->name != NULL; i++)
	{
		if (_strncmp(builtins_array.name, cmd, cmd_len + 1) == 0)
		{
			return (builtins_array[i].function);
		}
	}

	return (NULL);			
}
