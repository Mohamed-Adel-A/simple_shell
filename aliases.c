#include "shell.h"


builtin_alias(shell_data_t *sh_data)
{
	int i;
	char *tokens = sh_data->tokens;

	if (tokens[1] == NULL)
	{
		print_aliases(sh_data);
		return (0);
	}

	for(i = 0; tokens[i] != NULL; i++)
	{
		
	}
}



void print_aliases(shell_data_t *sh_data)
{
	int i;
	aliases_t *aliases = sh_data->aliases;

	if (aliases == NULL)
		return;
	for (i = 0 ; aliases[i] != NULL ; i++)
	{
		_puts(aliases[i][name]);
		_puts("=");
		_puts("\'");
		_puts(aliases[i][value]);
		_puts("\'");
		_puts("\n");
	}
}
