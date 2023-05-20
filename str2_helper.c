#include "shell.h"

/**
 * _strchar - find first occurrence of a character in string
 * @str: the string to be searched
 * @c: the character we want to find
 *
 * Return: index of the character, -1 if not found
 */
int _strchar(const char *str, char c)
{
	int i;
	const char *s = str;

	if (str == NULL)
		return (-1);

	for (i = 0 ; str[i] != '\0' ; i++)
	{
		if (str[i] == c)
			return (i);
	}

	if (str[i] == c)
		return (i);

	return (-1);
}
