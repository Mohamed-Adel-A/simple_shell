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

	if (str == NULL)
		return (NULL);

	for (; *str != '\0' ; str++)
	{
		if (*str == c)
			return (str);
	}

	if (*str == c)
		return (str);

	return (NULL);
}
