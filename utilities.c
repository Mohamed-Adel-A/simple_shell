#include "shell.h"


void handle_signal(int signal_no)
{
	if (signal_no == SIGINT)
	{
		puts("thats a signal\n");
	}
}
