#include "shell.h"


void handle_signal(int signal_no)
{
	if (signal_no == SIGINT)
	{
		/*fflush(stdin);*/
		write(STDIN_FILENO, "\n", 1);
		/*puts("\n");*/
		prompt();
	}
}
