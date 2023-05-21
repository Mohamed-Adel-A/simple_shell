#include "shell.h"

/**
 * _isnumber - check if string is number
 * @str: the string to be checked
 *
 * Retrun: 1 if str is number, 0 if not
 */
int _isnumber(const char *str)
{
	int i;

	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
	}

	if (str[i] == '+' || str[i] == '-')
	{
		i++;
	}

	for (; str[i] != '\0' ; i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return (0);
		}
	}

	return (1);
}



/**
 * _atoi - convert string to integer
 * @str: integer to be coverted
 *
 * Return: the converted integer
 */
int _atoi(const char *str)
{
	int minus = 1, number = 0, i = 0;

	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			minus = -1;
		}
		i++;
	}

	for ( ; str[i] >= '0' && str[i] <= '9' ; i++)
	{
		number = number * 10 + (str[i] - '0');
	}

	number = number * minus;
	return (number);
}
