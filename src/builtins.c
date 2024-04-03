/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:52:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/03 18:52:43 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// mudei retorno para 0 só para não executar as builtins por enquanto
int	is_builtin(t_token *cmd)
{
	if (!ft_strcmp(cmd->value, "echo") || !ft_strcmp(cmd->value, "cd")
		|| !ft_strcmp(cmd->value, "pwd") || !ft_strcmp(cmd->value, "export")
		|| !ft_strcmp(cmd->value, "unset") || !ft_strcmp(cmd->value, "env")
		|| !ft_strcmp(cmd->value, "exit"))
		return (0);
	return (0);
}
