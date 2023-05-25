#include "shell.h"

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
 * reallocate_line - reallocate line to new size
 * @line: the line
 * @n: size
 * @i: index
 *
 * Return: 0 success, -1 failure
 */
int reallocate_line(char *line, size_t *n, size_t i)
{
	char *new_line;

	if (i >= *n - 1)
	{
		if (*n < 120)
			*n = 120;
		else
			*n += 120;
		new_line = _realloc(line, *n, i - 1);
		if (new_line == NULL)
		{
			free(line);
			return (-1);
		}
		line = new_line;
	}
	return (0);
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
	size_t i = 0;
	char *lline = *lineptr, *new_line, c;

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
			new_line = _realloc(lline, *n, i);
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
	if (c == EOF && i == 0)/*here*/
	{
		free(lline);
		return (-1);
	}
	lline[i] = '\0';
	*lineptr = lline;
	return (i);
}




/**
 * check_empty_line - check if line is empty
 * @line: entered line
 *
 * Return: 1 if empty, 0 if not
 */
int check_empty_line(char *line)
{
	int i = 0;

	if (line == NULL)
		return (1);

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
	}
	return (1);
}



/**
 * getting_line - get line via getline and then check the line
 * @sh_data: shell data
 *
 * Return: 0 in success, -1 in failure
 */
int getting_line(shell_data_t *sh_data)
{
	ssize_t getline_ret;
	size_t line_len = 0;
	char *line = NULL;

	getline_ret = _getline(&line, &line_len, stdin);
	/*printf("%s\n", line);*/
	if (getline_ret == -1)
	{
		free_all(sh_data);
		/* _puts("\n");*/
		printf("exiting\n");
		exit(0);
	}
	else if (check_empty_line(line))
	{
		free(line);
		return (-1);
	}

	handle_comments(line);
	sh_data->line = line;
	sh_data->alltokens = tokenizing(line, " \n");
	return (0);
}
