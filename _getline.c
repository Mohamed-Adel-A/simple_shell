#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _getc - get char from stream
 * @stream: IO stream
 *
 * Return: char casting as int, or EOF otherwise
 */
int _getc(FILE *stream)
{
	char c;
	int rr;

	rr = read(stream->_fileno, &c, 1);

	if (rr > 0)
	{
		return ((int) c);
	}

	return (EOF);
}

/**
 * _getline - get line from stream
 * @lineptr: pointer to string
 * @n: line size
 * @stream: IO stream
 *
 * Return: size of the line or -1 in case of error
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char c;
	int i = 0;
	char *lline, *new_line;

	lline = *lineptr;
	if (lline == NULL)
	{
		lline = malloc(120 * sizeof(char));
		*n = 120;
		if (lline == NULL)
			return (-1);
	}

	while ((c = _getc(stream)) != EOF)
	{
		if (i >= *n - 1)
		{
			if (*n < 120)
				*n = 120;
			else
				*n += 120;
			new_line = realloc(lline, *n);
			if (new_line == NULL)
			{
				free(lline);
				return (-1);
			}
			lline = new_line;
		}
		lline[i] = c;
		i++;
		if (c == '\n')
			break;
	}
	if (c == EOF)
		return (-1);

	lline[i] = '\0';
	*lineptr = lline;
	return (i);
}
