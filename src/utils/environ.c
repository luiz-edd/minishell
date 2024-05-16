/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:18:32 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/16 16:39:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environ(void)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (__environ[i])
		i++;
	env_copy = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (__environ[++i])
		env_copy[i] = ft_strdup_calloc(__environ[i]);
	env_copy[i] = NULL;
	__environ = env_copy;
}

void	free_env(void)
{
	int	i;

	i = -1;
	while (__environ[++i])
		free(__environ[i]);
	free(__environ);
}

void	set_env(char *new_str, char *key, char *value)
{
	char	*env_var;

	env_var = getenv(key);
	if ((env_var || is_key_without_value(key)) && value != NULL)
		update_env(new_str, key);
	else if (!is_env_key_present(key))
		add_to_env(new_str);
}

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
