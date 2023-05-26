#include "shell.h"

/**
 * create_error - creat error msg
 * @sh_data: shell data
 * @err_msg: error msg
 * @cmd_arg_idx: if the error in arg in builtin cmd -> index, 0 otherwise
 *
 * Return: 0 success, -1 failure
 */
int create_error(shell_data_t *sh_data, char *err_msg, int cmd_arg_idx)
{
	int cmd_idx_len, argv_len, cmd_len, err_msg_len, cmd_arg_len = 0;
	int colons_and_spaces, full_err_len;
	char *argv, cmd_idx_str[20], *cmd, *cmd_arg = NULL, *full_err;

	argv = sh_data->argv[0];
	_itoa(sh_data->cmd_idx, cmd_idx_str);
	cmd = sh_data->tokens[0];

	argv_len = _strlen(argv);
	cmd_idx_len = _strlen(cmd_idx_str);
	cmd_len = _strlen(cmd);
	err_msg_len = _strlen(err_msg);
	colons_and_spaces = 6;

	/* not found path error */
	/* ./hsh: 1: ls: not found */
	
	if(cmd_arg_idx > 0)
	{
		/* built-in cmd error */
		/* ./hsh: 1: exit: Illegal number: -98 */
		/* ./hsh: 1: cd: can't cd to /hbtn */
		cmd_arg = sh_data->tokens[cmd_arg_idx];
		cmd_arg_len = _strlen(cmd_arg);	
	}

	full_err_len = argv_len + cmd_idx_len + cmd_len + err_msg_len + colons_and_spaces + cmd_arg_len;
	full_err = malloc(sizeof(char) * (full_err_len + 1));
	if (full_err == NULL)
		return (-1);

	_strcpy(full_err, argv);
	_strcat(full_err, ": ");
	_strcat(full_err, cmd_idx_str);
	_strcat(full_err, ": ");
	_strcat(full_err, cmd);
	_strcat(full_err, ": ");
	_strcat(full_err, err_msg);	
	_strcat(full_err, cmd_arg);
	printf("%s\n", full_err);
	
	free(full_err);
	return (0);
}
