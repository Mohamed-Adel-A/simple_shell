#include "shell.h"

/**
 * create_error - creat error msg
 * @sh_data: shell data
 * @err_msg: error msg
 * @cmd_arg_idx: if the error in arg in builtin cmd -> index, 0 otherwise
 *
 * Return: 0 success, -1 failure
 */
int create_error(shell_data_t *sh_data, char *err_msg, int cmd_arg_idx, int file_err)
{
	int cmd_idx_len = 0, argv_len = 0, cmd_len = 0, err_msg_len = 0, cmd_arg_len = 0;
	int colons_and_spaces, full_err_len;
	char *argv, cmd_idx_str[20], *cmd = NULL, *cmd_arg = NULL, *full_err;

	if (file_err == 1)
	{
		/* ./hsh: 0: Can't open /tmp/hbtn_checker_tmp_27147 */
		cmd_arg = sh_data->argv[1];
		cmd_arg_len = _strlen(cmd_arg);	
		colons_and_spaces = 6;
	}
	else
	{
		cmd = sh_data->tokens[0];
		cmd_len = _strlen(cmd);
		colons_and_spaces = 7;
	}

	argv = sh_data->argv[0];
	argv_len = _strlen(argv);

	_itoa(sh_data->cmd_idx, cmd_idx_str);
	cmd_idx_len = _strlen(cmd_idx_str);

	err_msg_len = _strlen(err_msg);

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

	if (file_err != 1)
	{
		_strcat(full_err, cmd);
		_strcat(full_err, ": ");
	}

	_strcat(full_err, err_msg);	
	_strcat(full_err, cmd_arg);
	_strcat(full_err, "\n");
	write(2, full_err, full_err_len);

	free(full_err);
	return (0);
}
