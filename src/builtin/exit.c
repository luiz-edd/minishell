/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:03:10 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/30 17:05:51 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(t_token *cmd)
{
	long	status;

	status = 0;
	if (cmd->next)
	{
		status = ft_atol(cmd->next->value);
		if (validate_argument(cmd->next->value) == FAILURE
			|| check_limits(status) == FAILURE)
		{
			ft_fprintf(STDERR_FILENO, "exit\nexit:\
%s: numeric argument required\n", cmd->next->value);
			exit(SYNTAX_ERROR);
		}
		if (cmd->next->next)
		{
			write(STDERR_FILENO, "exit: too many arguments\n", 26);
			exit(EXIT_FAILURE);
		}
	}
	printf("exit\n");
	delete_heredoc_files();
	ft_free_memory();
	exit(status % 256);
	return (SUCCESS);
}

int	validate_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	check_limits(long number)
{
	if (number < INT_MIN || number > INT_MAX)
		return (FAILURE);
	return (SUCCESS);
}
