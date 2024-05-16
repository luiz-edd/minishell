/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:16:10 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/16 16:06:55 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_unset(t_token *cmd)
{
	int		i;
	char	**args;
	int		status;

	i = 0;
	status = 0;
	args = get_cmd_and_args(cmd);
	if (!args[1])
		return (set_exit_status(status));
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]) && status++)
			continue ;
		delete_env_key(get_key(args[i]));
	}
	return (set_exit_status(!!status));
}

void	delete_env_key(char *key_to_delete)
{
	int		i;
	char	*env_key;

	i = -1;
	while (__environ[++i])
	{
		env_key = get_key(__environ[i]);
		if (!ft_strcmp(key_to_delete, env_key))
		{
			__environ[i] = NULL;
			break ;
		}
	}
}
