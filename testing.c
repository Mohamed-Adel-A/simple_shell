#include "main.h"
#include <string.h>

int main(void)
{
  char line[] = "This is a test line\n";
  char *new_line = _strdup(line);

	printf("%s, %p\n", line, line);
	printf("%s, %p\n", new_line, new_line);
	
	return (1);	
}
