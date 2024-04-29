/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fd_restore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:31:49 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/29 17:46:16 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	restore_fds(void)
{
	int	*std_fd;

	std_fd = get_fds();
	dup2(std_fd[STDIN_FILENO], STDIN_FILENO);
	dup2(std_fd[STDOUT_FILENO], STDOUT_FILENO);
	dup2(std_fd[STDERR_FILENO], STDERR_FILENO);
}
