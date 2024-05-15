/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:16:29 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/15 20:18:06 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(char *new_str, char *key)
{
	int		i;
	char	*env_key;
	char	*aux;

	i = -1;
	while (__environ[++i])
	{
		env_key = get_key(__environ[i]);
		if (!ft_strcmp(key, env_key))
		{
			aux = __environ[i];
			__environ[i] = ft_strdup_calloc(new_str);
			free(aux);
			break ;
		}
	}
}

int	is_key_exist(char *key)
{
	int		i;
	char	*env_key;

	i = -1;
	while (__environ[++i])
	{
		env_key = get_key(__environ[i]);
		if (!ft_strcmp(key, env_key))
			return (1);
	}
	return (0);
}

int	is_key_exist_whitout_content(char *key)
{
	int		i;
	char	*env_key;

	i = -1;
	while (__environ[++i])
	{
		if (!ft_strchr(__environ[i], '='))
		{
			env_key = get_key(__environ[i]);
			if (!ft_strcmp(key, env_key))
				return (1);
		}
	}
	return (0);
}

static void	ft_set_env(char *new_str, char *key, char *content)
{
	char	*env_var;

	env_var = getenv(key);
	if ((env_var || is_key_exist_whitout_content(key)) && content != NULL)
		update_env(new_str, key);
	else if (!is_key_exist(key))
		(add_to_env(new_str));
}

// export key=content
int	execute_export(t_token *cmd)
{
	int		i;
	char	**args;
	char	*equal_sign;
	char	*key;
	int		status;

	i = 0;
	status = 0;
	args = get_cmd_and_args(cmd);
	if (!args[1])
		print_environ_sorted();
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]) && status++)
			continue ;
		key = get_key(args[i]);
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			ft_set_env(args[i], key, equal_sign + 1);
		else
			ft_set_env(args[i], key, NULL);
	}
	return (set_exit_status(!!status));
}
