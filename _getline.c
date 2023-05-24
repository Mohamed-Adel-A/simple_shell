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

	return (rr);
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
	static size_t i;
	char *lline = *lineptr, *new_line, c = 's';
	size_t m;

	if (i != 0)
		return(-1);
	else
		fflush(stdin);		

	i = 0;
	if (lline == NULL)
	{
		lline = malloc(120 * sizeof(char));
		*n = 120;
		if (lline == NULL)
			return (-1);
	}
	while (c != '\n')
	{
		
		c = _getc(stream);
		if ((c == 0 && i == 0) ||c == -1)
		{
			free(lline);
			return (-1);
		}
		if (c == 0)
		{
			i++;
			break;
		}
		
		if (c == 27)
		{
			_getc(stream);
			_getc(stream);
			/*continue;*/
		}
		if (i >= *n - 1)
		{
			if (*n < 120)
				*n = 120;
			else
				*n += 120;
			new_line = _realloc(lline, *n);
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

	lline[i] = '\0';
	m = i;
	if (c != 0)
		i = 0;
	*lineptr = lline;
	return (m);
}





/**
 * check_empty_line - check if line is empty
 * @line: entered line
 *
 * Return: 1 in success, 0 in failure
 */
int check_empty_line(const char *line)
{
	int i = 0;

	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
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
	fflush(stdin);
	if (getline_ret == -1)
	{
		free_all(sh_data);
		/* _puts("\n");*/
		exit(EXIT_SUCCESS);
	}
	else if (check_empty_line(line))
	{
		free(line);
		return (-1);
	}

	handle_comments(line);
	sh_data->line = line;
	sh_data->tokens = tokenizing(line, " \n");
	return (0);
}
