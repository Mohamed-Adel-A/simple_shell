#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _strlen - return the length of a string
 * @s: the string
 *
 * Return: (int) the lenght of the string
 */
int _strlen(const char *s)
{
	int i;

	if (!s)
		return (0);

	for (i = 0 ; s[i] != '\0' ; i++)
	{
	}
	return (i);
}


/**
 * _strcpy - copy string from src to dest
 * @dest: pointer to destination string
 * @src: pointer to source string
 *
 * Return: pointer to destination string
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	if (src == NULL)
		return (dest);

	for (i = 0 ; src[i] != '\0' ; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}



/**
 * _strdup - duplicate strings
 * @src: source string
 *
 * Return: douplicated string
 */
char *_strdup(const char *src)
{
	int i, str_len;
	char *duplicated_string;

	if (src == NULL)
		return (NULL);

	str_len = _strlen(src);

	duplicated_string = malloc((str_len + 1) * sizeof(char));
	if (duplicated_string == NULL)
		return (NULL);

	_strcpy(duplicated_string, src);

	return (duplicated_string);
}



/**
 * _strncmp - cmpare the first n char of two strings
 * @s1: the first string
 * @s2: the second string
 * @n: the number of char to be compared
 *
 * Return: 0 if s1 == s2, otherwise (s1 - s2)
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;

	if (s1 == NULL && s2 == NULL)
		return (0);

	for (i = 0 ; i < n ; i++)
	{
		if ((s1[i] == s2[i]) && ((i == n - 1) || (s1[i] == '\0')))
		{
			return (0);
		}
		else if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}

	return (0);
}
