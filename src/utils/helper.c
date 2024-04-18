/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:32:27 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/18 19:03:02 by pehenri2         ###   ########.fr       */
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
/*
void	wait_for_all_children(void)
{
	while (wait(NULL != -1))
		;
}
*/

int	last_exit_status_holder(int status)
{
	static int	exit_status = 0;

	if (status != CHECK_LAST_VALUE)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = WTERMSIG(status) + 128;
		else
			exit_status = status;
	}
	return (exit_status);
}
