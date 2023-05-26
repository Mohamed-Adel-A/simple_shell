#include "shell.h"

int create_error(shell_data_t *sh_data)
{
	int i, cmd_idx_len, argv_len, token_len, err_msg_len;
	char cmd_idx_str[20];

	cmd_idx_str = _itoa(sh_data->cmd_idx, cmd_idx_str);

	argv_len = _strlen(sh_data->argv[0]);
	cmd_idx_len = _strlen(cmd_idx_str);
	token_len = _strlen(sh_data->tokens[0]);
	if()
	{
	}
	
	
	_strlen
}
