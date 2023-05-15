#include "shell.h"
#include <string.h>

int main(void)
{
  char line[] = "This is a test line\n";
  char *new_line = NULL;
	char **tokens = NULL;
	int i = 0;
	size_t line_len = 0;
	
	_getline(&new_line, &line_len, stdin);
	
	
	tokens = tokenizing(line);

	for (i = 0 ; tokens[i] != NULL ; i++)
	{
		printf("%s\n len: %i, %p\n", tokens[i], _strlen(tokens[i]), tokens[i]);
	}

	printf("%s len: %i, %p\n", line, _strlen(line), line);
	printf("%s len: %i, %p\n", new_line, _strlen(new_line), new_line);
	
	free(tokens);
	free(new_line);	
	return (1);	
}
