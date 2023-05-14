#include "main.h"
#include <string.h>

int main(void)
{
  char line[] = "This is a test line\n";
  char *token = NULL, *delima = " \n";

	token = strtok(line, delima);
	printf("%s, %p\n", line, line);
	printf("%s, %p\n", token, token[5]);
	
	return (1);	
}
