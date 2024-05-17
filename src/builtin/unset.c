/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:16:10 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/17 15:51:36 by leduard2         ###   ########.fr       */
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
	int		j;
	char	*env_key;
	char	**new_env;
	char	**env;

	env = *get_my_env();
	i = 0;
	while (env[i])
		i++;
	new_env = (char **)ft_calloc(i, (sizeof(char *)));
	i = -1;
	j = -1;
	while (env[++i])
	{
		env_key = get_key(env[i]);
		if (ft_strcmp(key_to_delete, env_key))
			new_env[++j] = env[i];
	}
	new_env[j + 1] = NULL;
	*get_my_env() = new_env;
	__environ = new_env;
	i = -1;
}

// export aaa=10 && export bbb=20 && export ccc=30 && export ddd=40