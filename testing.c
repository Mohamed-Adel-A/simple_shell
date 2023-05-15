#include "main.h"
#include <string.h>

int main(void)
{
  char line[] = "This is a test line\n";
  char *new_line = _strdup(line);

	printf("%s len: %i, %p\n", line, _strlen(line), line);
	printf("%s len: %i, %p\n", new_line, _strlen(new_line), new_line);
	
	return (1);	
}
