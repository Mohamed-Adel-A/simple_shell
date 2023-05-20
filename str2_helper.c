#include "shell.h"

/**
 * _strchar - find first occurrence of a character in string
 * @str: the string to be searched
 * @c: the character we want to find
 *
 * Return: pointer to the character, NULL if not found
 */
char *_strchar(const char *str, char c)
{
	int i;
	const char *s = str;

	if (str == NULL)
		return (NULL);

	for (i = 0 ; str[i] != '\0' ; i++)
	{
		if (str[i] == c)
			return (s + i);
	}

	if (str[i] == c)
		return (s + i);

	return (NULL);
}
