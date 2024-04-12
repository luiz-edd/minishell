/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:51:33 by leduard2          #+#    #+#             */
/*   Updated: 2024/04/12 16:53:00 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (!ft_strcmp(cmd->value, "echo") || !ft_strcmp(cmd->value, "cd")
// 		|| !ft_strcmp(cmd->value, "pwd") || !ft_strcmp(cmd->value, "export")
// 		|| !ft_strcmp(cmd->value, "unset") || !ft_strcmp(cmd->value, "env")
// 		|| !ft_strcmp(cmd->value, "exit"))

int	execute_builtin(t_token *cmd)
{
	char *str;

	str = cmd->value;
	if (!ft_strcmp(str, "echo"))
		return (execute_echo(cmd));
	if (!ft_strcmp(cmd->value, "pwd"))
		return (execute_pwd());
	if (!ft_strcmp(cmd->value, "cd"))
		return (execute_cd(cmd));
	return (handle_error("error execute builtin"));
}