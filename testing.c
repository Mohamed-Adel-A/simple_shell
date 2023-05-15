#include "shell.h"
#include <string.h>

int main(void)
{
  char line[] = "This is a test line\n";
  char *new_line = NULL;
	char **tokens = NULL;
	int i = 0;
	size_t line_len = 0;
	pid_t cpid;
	char *cmd[] = {"bin/ls", NULL};
	
	_getline(&new_line, &line_len, stdin);
	
	
	tokens = tokenizing(new_line);

	for (i = 0 ; tokens[i] != NULL ; i++)
	{
		printf("%s\n len: %i, %p\n", tokens[i], _strlen(tokens[i]), tokens[i]);
	}

	printf("%s len: %i, %p\n", line, _strlen(line), line);
	printf("%s len: %i, %p\n", new_line, _strlen(new_line), new_line);
	
	cpid = fork();
	if (cpid = 0)
	{
		execve(cmd[0], cmd, NULL);
	}
	else
	{
		wait(NULL);
		printf("error");
	}
	
	free(tokens);
	free(new_line);	
	return (1);	
}
