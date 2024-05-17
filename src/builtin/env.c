/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:29:57 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/17 15:40:44 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_token *cmd)
{
	int	i;
	char **env;

	env = *get_my_env();
	if (cmd->next)
		return (!!write(STDERR_FILENO, "env: too many arguments", 24));
	i = -1;
	while (env[++i])
	{
		if (env[i][0] && ft_strchr(env[i], '='))
			ft_fprintf(STDOUT_FILENO, "%s\n", env[i]);
	}
	return (SUCCESS);
}
