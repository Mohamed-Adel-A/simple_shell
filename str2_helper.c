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


/**
 * _strncpy - copy string from src to dest
 * @dest: pointer to destination string
 * @src: pointer to source string
 * @n: number of character to be copied
 *
 * Return: pointer to destination string
 */
char *_strncpy(char *dest, const char *src, int n)
{
	int i;

	if (src == NULL || n == 0)
		return (dest);

	for (i = 0 ; src[i] != '\0' && i < n ; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

