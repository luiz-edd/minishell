/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:21:11 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/23 21:46:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	return (set_exit_status(SYNTAX_ERROR));
}

int	throw_error(char *cmd_path)
{
	if (access(cmd_path, X_OK) == -1 && !access(cmd_path, F_OK))
		return (126 + write(STDERR_FILENO, "minishell: Permission denied\n", 30) - 30);
	else if ((*cmd_path == '/' || *cmd_path == '.') && !access(cmd_path, F_OK))
		return (126 + write(STDERR_FILENO, "minishell: Is a directory\n", 27) - 27);
	else if (errno == 2 && !(*cmd_path == '/' || *cmd_path == '.'))
		return (127 + write(STDERR_FILENO, "minishell: command not found\n", 30) - 30);
	else if (errno == 2 || !getenv("PATH"))
		return (127 + write(STDERR_FILENO, "minishell: No such file or directory\n", 38) - 38);
	else
		return (!!errno + write(STDERR_FILENO, "minishell: unexpected error\n", 28) - 28);
}

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
