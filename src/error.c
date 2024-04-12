/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:21:11 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/12 14:59:35 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	return (FAILURE);
}

int	handle_error(char *message)
{
	if (errno)
	{
		perror(message);
		ft_free_memory();
		return (errno);
	}
	else
	{
		dprintf(STDERR_FILENO, "%s\n", message);
		ft_free_memory();
		return (FAILURE);
	}
}

void	panic_exit(char *message)
{
	if (errno)
	{
		perror(message);
		ft_free_memory();
		exit(errno);
	}
	else
	{
		dprintf(STDERR_FILENO, "%s\n", message);
		ft_free_memory();
		exit(FAILURE);
	}
}

void	close_pipe(int *pipe_fd)
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

void	exit_status(int status)
{
	ft_free_memory();
	exit(status);
}
void	exit_success(void)
{
	ft_free_memory();
	exit(SUCCESS);
}

void	exit_failure(void)
{
	ft_free_memory();
	exit(errno);
}
