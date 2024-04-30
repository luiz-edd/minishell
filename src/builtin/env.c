/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:29:57 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/30 15:59:02 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_token *cmd)
{
	int	i;

	if (cmd->next)
		return (handle_error("env: too many arguments"));
	i = 0;
	while (__environ[i])
	{
		if (ft_strchr(__environ[i], '='))
			ft_fprintf(STDOUT_FILENO, "%s\n", __environ[i]);
		i++;
	}
	return (SUCCESS);
}
