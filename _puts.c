#include "shell.h"

/**
 * _putchar - putchar to stdout
 * @c: char to be put
 *
 * Return: 1 on success, -1 on error
 */

int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * _puts - print string to stdout
 * @s: string to be printed
 *
 * Return: size of string that was printed
 */
int _puts(const char *s)
{
	int i = 0, r;

	if (s == NULL)
		return (0);
	for (i = 0 ; s[i] != '\0' ; i++)
	{
		r = _putchar(s[i]);
		if (r == -1)
			return (EOF);
	}
	return (i);
}

