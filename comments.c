#include "shell.h"

/**
 * handle_comments - handle comments in entered line
 * @line: pointer to string line
 *
 * Return: 0 in success, -1 otherwise
 */
int handle_comments(char *line)
{
	int i;

	if (line == NULL)
		return (-1);

	for (i = 0 ; line[i] != '#' && line[i] != '\0' ; i++)
	{
	}
	if (i == 0 && line[i] = '#')
		line[i] = '\0';;
	else if (line[i] == '#' && line[i - 1] == ' ')
	{
		line[i - 1] = '\0';
	}

	return (0);
}
