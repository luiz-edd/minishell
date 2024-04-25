/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:32:27 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/25 20:55:33 by pehenri2         ###   ########.fr       */
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
	else if (status > 256)
		*exit_status = status - 256;
	else if (WIFSIGNALED(status))
		*exit_status = WTERMSIG(status) + 128;
	else
		*exit_status = status;
	return (*exit_status);
}
