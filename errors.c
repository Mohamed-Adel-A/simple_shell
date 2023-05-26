#include "shell.h"

int create_error(shell_data_t *sh_data, char *err_msg, int cmd_arg_idx, int arg_colon)
{
	int i, cmd_idx_len, argv_len, cmd_len, err_msg_len, cmd_arg_len = 0;
	int colons_number, full_err_len;
	char *argv, cmd_idx_str[20], *cmd, *cmd_arg = NULL, *full_msg;

	argv = sh_data->argv[0];
	cmd_idx_str = _itoa(sh_data->cmd_idx, cmd_idx_str);
	cmd = sh_data->tokens[0];

	argv_len = _strlen(argv);
	cmd_idx_len = _strlen(cmd_idx_str);
	cmd_len = _strlen(cmd);
	err_msg_len = _strlen(err_msg);
	colons_number = 3 + arg_colon;

	/* not found path error */
	/* ./hsh: 1: ls: not found */
	
	full
	if(cmd_arg_idx > 0)
	{
		cmd_arg = sh_data->tokens[cmd_arg_idx];
		cmd_arg_len = _strlen(cmd_arg);
		
	}
	full_err_len = arg
	
	
	
	_strlen
}
