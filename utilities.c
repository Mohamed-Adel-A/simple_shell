#include "shell.h"

/**
 * handle_signal - handle signals
 * @signal_no: signal number
 *
 * Return: void
 */
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
