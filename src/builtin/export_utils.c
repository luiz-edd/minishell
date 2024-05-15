/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:16:23 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/15 20:17:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(char *str)
{
	char	**new_env;
	int		i;

	i = 0;
	while (__environ[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (__environ[++i])
		new_env[i] = __environ[i];
	new_env[i++] = ft_strdup_calloc(str);
	new_env[i] = NULL;
	free(__environ);
	__environ = new_env;
}

int	is_valid_identifier(char *str)
{
	if (*str != '=' && !ft_isdigit(*str))
	{
		while (*str && *str != '=' && (ft_isalnum(*str) || *str == '_'))
			str++;
		if (*str == '=' || !*str)
			return (1);
	}
	ft_putendl_fd("minishell: export: not a valid identifier", 2);
	set_exit_status(1);
	return (0);
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
