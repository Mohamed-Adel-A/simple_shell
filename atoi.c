#include "shell.h"

/**
 * _isnumber - check if string is number
 * @str: the string to be checked
 *
 * Return: 1 if str is number, 0 if not
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
		if ((str[i] < '0' || str[i] > '9'))
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

/**
 * _itoa - convert integer to sting
 * @int_value: integer value to be converted
 * @str: pointer to string that will contain the string
 *
 * Return: pointer to string NULL otherwise
 */
char *_itoa(int int_value, char *str)
{
	int str_idx = 0, rev_idx = 0;
	char reversed[20];

	if (str == NULL)
		return (NULL);

	if (int_value < 0)
	{
		str[str_idx] = '-';
		int_value *= -1;
		str_idx++;
	}

	while (int_value != 0)
	{
		reversed[rev_idx] = int_value % 10 + '0';
		int_value = int_value / 10;
		rev_idx++;
	}

	for (rev_idx-- ; rev_idx >= 0 ; rev_idx--)
	{
		str[str_idx] = reversed[rev_idx];
		str_idx++;
	}
	str[str_idx] = '\0';

	return (str);
}

