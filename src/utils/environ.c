/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:18:32 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/17 16:02:23 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***get_my_env(void)
{
	static char	**env;

	return (&env);
}

void	init_environ(void)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (__environ[i])
	{
		// printf("%s\n", __environ[i]);
		i++;
	}
	*get_my_env() = malloc(sizeof(char *) * (i + 1));
	env_copy = *get_my_env();
	i = -1;
	while (__environ[++i])
		env_copy[i] = ft_strdup_calloc(__environ[i]);
	env_copy[i] = NULL;
	__environ = env_copy;
	// 	i = 0;
	// 	while (env_copy[i])
	// 	{
	// 		printf("%s\n", env_copy[i]);
	// 		printf("i: %d\n", i);
	// 		i++;
	// 	}
}

void	free_env(void)
{
	int		i;
	char	**env;

	i = -1;
	env = *get_my_env();
	while (env[++i])
	{
		free(env[i]);
	}
	free(env);
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
	char	**env;

	env = *get_my_env();
	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i++] = ft_strdup_calloc(str);
	new_env[i] = NULL;
	free(env);
	*get_my_env() = new_env;
	__environ = new_env;
}

void	update_env(char *new_str, char *key)
{
	int		i;
	char	*env_key;
	char	*aux;
	char	**env;

	env = *get_my_env();
	i = -1;
	while (env[++i])
	{
		env_key = get_key(env[i]);
		if (!ft_strcmp(key, env_key))
		{
			aux = env[i];
			env[i] = ft_strdup_calloc(new_str);
			free(aux);
			break ;
		}
	}
	*get_my_env() = env;
	__environ = env;
}
