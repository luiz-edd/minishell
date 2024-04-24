/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:21:11 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/24 17:33:06 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token)
{
	dprintf(2, "minishell: syntax error near unexpected token `%s'\n", token);
	return (set_exit_status(SYNTAX_ERROR));
}

// int	write_message_return_error(char *message, int num)
// {
// 	write(STDERR_FILENO, message, ft_strlen(message));
// 	return (num)
// }

int    throw_error(char *cmd_path)
{
    if (access(cmd_path, X_OK) == -1 && !access(cmd_path, F_OK))
    {
        dprintf(STDERR_FILENO, "%s: Permission denied\n", cmd_path);
        return (126);
    }
    else if ((*cmd_path == '/' || *cmd_path == '.') && !access(cmd_path, F_OK))
    {
        dprintf(STDERR_FILENO, "%s: Is a directory\n", cmd_path);
        return (126);
    }
    else if (errno == 2 && !(*cmd_path == '/' || *cmd_path == '.'))
    {
        dprintf(STDERR_FILENO, "%s: command not found\n", cmd_path);
        return (127);
    }
    else if (errno == 2 || !getenv("PATH"))
    {
        dprintf(STDERR_FILENO, "%s: No such file or directory\n", cmd_path);
        return (127);
    }
    else
        return (!!errno + write(STDERR_FILENO, "minishell: unexpected error\n", 28) - 28);
}

// int	throw_error(char *cmd_path)
// {
// 	if (access(cmd_path, X_OK) == -1 && !access(cmd_path, F_OK))
// 		return (126, write_and_return_error("minishell: Permission denied\n"));
// 	else if ((*cmd_path == '/' || *cmd_path == '.') && !access(cmd_path, F_OK))
// 		return (126, write_and_return_error("minishell: Is a directory\n"));
// 	else if (errno == 2 && !(*cmd_path == '/' || *cmd_path == '.'))
// 		return (127, write_and_return_error("minishell: command not found\n"));
// 	else if (errno == 2 || !getenv("PATH"))
// 		return (127,
// 			write_and_return_error("minishell: No such file or directory\n"));
// 	else
// 		return (1,
				// write_and_return_error("minishell: No such file or directory\n"));
// }

int	handle_error(char *message)
{
	perror(message);
	ft_free_memory();
	return (!!errno);
}

void	close_pipe(int *pipe_fd)
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

void	free_and_exit(int status)
{
	ft_free_memory();
	if (status == SUCCESS)
		exit(SUCCESS);
	else if (errno)
		exit(errno);
	else
		exit(status);
}
