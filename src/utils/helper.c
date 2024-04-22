/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:32:27 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/22 18:09:12 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_all_children(void)
{
	int	status;
	int	pid;

	while (42)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid <= 0)
			break ;
	}
}

int	*get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

int	set_exit_status(int status)
{
	int	*exit_status;

	exit_status = get_exit_status();
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_status = WTERMSIG(status) + 128;
	else
		*exit_status = status;
	return (*exit_status);
}

int	*get_fds(void)
{
	static int	fd[3];

	return (fd);
}

void	save_std_fd(void)
{
	int	*fd;

	fd = get_fds();
	fd[STDIN_FILENO] = dup(STDIN_FILENO);
	fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	fd[STDERR_FILENO] = dup(STDERR_FILENO);
}

void	revert_fds(void)
{
	int	*std_fd;

	std_fd = get_fds();
	dup2(std_fd[STDIN_FILENO], STDIN_FILENO);
	dup2(std_fd[STDOUT_FILENO], STDOUT_FILENO);
	dup2(std_fd[STDERR_FILENO], STDERR_FILENO);
}
