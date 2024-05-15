/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:52:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/14 16:24:42 by leduard2         ###   ########.fr       */
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
		|| !ft_strcmp(cmd->value, "cd") || !ft_strcmp(cmd->value, "exit")
		|| !ft_strcmp(cmd->value, "env") || !ft_strcmp(cmd->value, "export")
		|| !ft_strcmp(cmd->value, "unset"))
		return (1);
	return (0);
}

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
	if (!ft_strcmp(cmd->value, "env"))
		return (execute_env(cmd));
	if (!ft_strcmp(cmd->value, "exit"))
		return (execute_exit(cmd));
	if (!ft_strcmp(cmd->value, "export"))
		return (execute_export(cmd));
	if (!ft_strcmp(cmd->value, "unset"))
		return (execute_unset(cmd));
	return (handle_error("error executing builtin"));
}
