/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:52:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/12 17:25:03 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (!ft_strcmp(cmd->value, "echo") || !ft_strcmp(cmd->value, "cd")
// 	|| !ft_strcmp(cmd->value, "pwd") || !ft_strcmp(cmd->value, "export")
// 	|| !ft_strcmp(cmd->value, "unset") || !ft_strcmp(cmd->value, "env")
// 	|| !ft_strcmp(cmd->value, "exit"))
// mudei retorno para 0 só para não executar as builtins por enquanto
int	is_builtin(t_token *cmd)
{
	if (!ft_strcmp(cmd->value, "echo") || !ft_strcmp(cmd->value, "pwd")
			|| !ft_strcmp(cmd->value, "cd"))
		return (1);
	return (0);
}
