/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:36:14 by leduard2          #+#    #+#             */
/*   Updated: 2024/04/12 14:56:51 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(char **args, int has_n_flag)
{
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
		args++;
	}
	if (!has_n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	check_n_flag(char *str)
{
	if (*str == '-' && *(str + 1) == 'n')
	{
		str++;
		while (*str == 'n')
			str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}

int	execute_echo(t_token *cmd)
{
	char	**args;
	int		has_n_flag;

	has_n_flag = 0;
	args = get_cmd_and_args(cmd);
	args++;
	while (*args && check_n_flag(*args))
	{
		has_n_flag = 1;
		args++;
	}
	print_args(args, has_n_flag);
	return (SUCCESS);
}
