/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:16:29 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/22 17:50:05 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!is_valid_identifier(args[i], args[0]) && ++status)
			continue ;
		key = get_key(args[i]);
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			set_env(args[i], key, equal_sign + 1);
		else
			set_env(args[i], key, NULL);
	}
	return (set_exit_status(!!status));
}

char	*get_key(char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (ft_strdup(arg));
	else
		return (ft_strndup(arg, equal_sign - arg));
}

int	is_valid_identifier(char *str, char *cmd_name)
{
	if (*str != '=' && !ft_isdigit(*str) && *str != '\0')
	{
		while (*str && *str != '=' && (ft_isalnum(*str) || *str == '_'))
			str++;
		if (*str == '=' || !*str)
			return (1);
	}
	ft_fprintf(STDERR_FILENO, "%s: not a valid identifier\n", cmd_name);
	set_exit_status(FAILURE);
	return (0);
}

int	is_env_key_present(char *key)
{
	int		i;
	char	*env_key;
	char	**env;

	env = *get_my_env();
	i = -1;
	while (env[++i])
	{
		env_key = get_key(env[i]);
		if (!ft_strcmp(key, env_key))
			return (1);
	}
	return (0);
}

int	is_key_without_value(char *key)
{
	int		i;
	char	*env_key;
	char	**env;

	env = *get_my_env();
	i = -1;
	while (env[++i])
	{
		if (!ft_strchr(env[i], '='))
		{
			env_key = get_key(env[i]);
			if (!ft_strcmp(key, env_key))
				return (1);
		}
	}
	return (0);
}
