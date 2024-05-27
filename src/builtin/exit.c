/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:03:10 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/27 14:55:47 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(t_token *cmd)
{
	long	status;

	status = 0;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_fprintf(STDOUT_FILENO, "exit\n");
	if (cmd->next)
	{
		status = ft_atol(cmd->next->value);
		if (validate_argument(cmd->next->value) || *(cmd->next->value) == '\0')
		{
			ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n", \
cmd->next->value);
			exit(SYNTAX_ERROR);
		}
		if (cmd->next->next)
			return (!!write(STDERR_FILENO, "exit: too many arguments\n", 25));
	}
	delete_heredoc_files();
	ft_free_memory();
	free_env();
	if (status)
		exit(status % 256);
	exit(*get_exit_status());
}

int	validate_argument(char *arg)
{
	int		i;
	char	sign;

	i = 0;
	sign = '+';
	if (arg[i] == '-' || arg[i] == '+')
	{
		sign = arg[i];
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FAILURE);
		i++;
	}
	if (check_limits(arg, sign) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_limits(char *arg, char sign)
{
	if (*arg == '+' || *arg == '-')
		arg++;
	if (ft_strlen(arg) > 19)
		return (FAILURE);
	if ((ft_strcmp(arg, "9223372036854775807") > 0 && sign == '+')
		|| (ft_strcmp(arg, "9223372036854775808") > 0 && sign == '-'))
		return (FAILURE);
	return (SUCCESS);
}
