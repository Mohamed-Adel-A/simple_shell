#include "shell.h"
#include <string.h>

int main(void)
{
  char *line = NULL;
	char **tokens = NULL;
	int exe_st;
	size_t line_len = 0;
	ssize_t getline_ret;
	pid_t cpid;
	/**char *cmd[] = {"/bin/ls", "-l", NULL};*/

	while (1)
	{
		line = NULL;
		tokens = NULL;
		line_len = 0;
		
		_puts(">>> ");
		
	getline_ret = _getline(&line, &line_len, stdin);
		if (getline_ret == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
	tokens = tokenizing(line);
	
	cpid = fork();
	if (cpid == 0)
	{
		exe_st = execve(tokens[0], tokens, NULL);
		if (exe_st == -1)
			printf("Error: No such file or directory\n");
	}
	else
	{
		wait(NULL);
		printf("Done %i\n", exe_st);
	}
	
	
	free(tokens);
	free(line);	
	}
	return (1);	
}
