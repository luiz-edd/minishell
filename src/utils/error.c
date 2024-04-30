/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:21:11 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/30 15:57:38 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token)
{
	ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n", token);
	return (set_exit_status(SYNTAX_ERROR));
}

// erro quando passa um diretorio sozinho entra no ultimo else só que o
// status tem que ser 127
int	throw_error(char *cmd_path)
{
	if (access(cmd_path, X_OK) == -1 && !access(cmd_path, F_OK))
	{
		ft_fprintf(STDERR_FILENO, "%s: Permission denied\n", cmd_path);
		return (126);
	}
	else if ((*cmd_path == '/' || *cmd_path == '.') && !access(cmd_path, F_OK))
	{
		ft_fprintf(STDERR_FILENO, "%s: Is a directory\n", cmd_path);
		return (126);
	}
	else if (errno == 2 && !(*cmd_path == '/' || *cmd_path == '.'))
	{
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd_path);
		return (127);
	}
	else if (errno == 2 || !getenv("PATH"))
	{
		ft_fprintf(STDERR_FILENO, "%s: No such file or directory\n", cmd_path);
		return (127);
	}
	else
		return (!!errno
			+ write(STDERR_FILENO, "minishell: unexpected error\n", 28) - 28);
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
