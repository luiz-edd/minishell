/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:21:11 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/23 18:51:14 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	return (set_exit_status(SYNTAX_ERROR));
}

// trocar checagem para valor do errno e então "traduzir" o erro para o bash
// assim o trabalho fica com o execve e não com o minishell
int throw_error(char *cmd_path)
{
	if (access(cmd_path, R_OK | W_OK) == -1 && !access(cmd_path, F_OK))
		return (126 + write(2, "minishell: Permission denied", 28) - 28);
	else if ((*cmd_path == '/' || *cmd_path == '.') && !access(cmd_path, F_OK))
		return(126 + write(2, "minishell: Is a directory", 25) - 25);
	else if (!search_command(cmd_path) && !(*cmd_path == '/' || *cmd_path == '.'))
		return(127 + write(2,"minishell: command not found", 27) - 27);
	else if (!search_command(cmd_path) || !ft_getenv("PATH"))
		return(127 + write(2,"minishell: No such file or directory", 37) - 37);
	else
		return(!!errno + write(2, "minishell: unexpected error", 28) - 28);
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
