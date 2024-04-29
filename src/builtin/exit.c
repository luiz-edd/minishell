/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:03:10 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/29 17:53:59 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(t_token *token_list)
{
	long	status;

	status = 0;
	if (token_list->next)
	{
		status = ft_atol(token_list->next->value);
		if (validate_argument(token_list->next->value) == FAILURE
			|| check_limits(status) == FAILURE)
		{
			dprintf(STDERR_FILENO, "exit\nexit:\
%s: numeric argument required\n", token_list->next->value);
			exit(SYNTAX_ERROR);
		}
		if (token_list->next->next)
		{
			dprintf(STDERR_FILENO, "exit: too many arguments\n");
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
