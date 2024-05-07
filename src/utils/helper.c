/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:32:27 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/07 14:50:55 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

int	set_exit_status(int status)
{
	int	*exit_status;

	exit_status = get_exit_status();
	*exit_status = status;
	return (*exit_status);
}

void	wait_child_status(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (*status == 1)
		return ;
	else if (WIFSIGNALED(*status))
	{
		write(STDIN_FILENO, "\n", 1);
		*status = WTERMSIG(*status) + 128;
	}
}

void	reset_for_next_iteration(char *line)
{
	free(line);
	delete_heredoc_files();
	ft_free_memory();
}
