/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:52:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/27 22:48:05 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (!ft_strcmp(cmd->value, "echo") || !ft_strcmp(cmd->value, "cd")
// 	|| !ft_strcmp(cmd->value, "pwd") || !ft_strcmp(cmd->value, "export")
// 	|| !ft_strcmp(cmd->value, "unset") || !ft_strcmp(cmd->value, "env")
// 	|| !ft_strcmp(cmd->value, "exit"))
int	is_builtin(t_token *cmd)
{
	if (!ft_strcmp(cmd->value, "echo") || !ft_strcmp(cmd->value, "pwd")
		|| !ft_strcmp(cmd->value, "cd"))
		return (1);
	return (0);
}

// provavelmente se der erro o retorno e 1, se sucesso = 0
int	execute_builtin(t_token *cmd)
{
	char	*str;

	str = cmd->value;
	if (!ft_strcmp(str, "echo"))
		return (execute_echo(cmd));
	if (!ft_strcmp(cmd->value, "pwd"))
		return (execute_pwd());
	if (!ft_strcmp(cmd->value, "cd"))
		return (execute_cd(cmd));
	return (handle_error("error execute builtin"));
}
