/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:16:16 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/23 21:02:45 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_environ_sorted(void)
{
	char	*printed;
	size_t	size;
	char	**env;

	env = *get_my_env();
	size = 0;
	while (env[size])
		size++;
	printed = ft_calloc(size + 1, sizeof(char));
	while (print_smallest_unprinted(env, size, printed))
		;
	free(printed);
}

int	print_smallest_unprinted(char **env, size_t env_size, char *printed)
{
	int	smallest_pos;

	smallest_pos = -1;
	while (env_size-- > 0)
	{
		if (printed[env_size])
			continue ;
		if (smallest_pos == -1)
			smallest_pos = env_size;
		else
		{
			if (ft_strcmp(env[smallest_pos], env[env_size]) > 0)
				smallest_pos = env_size;
		}
	}
	if (smallest_pos != -1)
	{
		format_and_print(env[smallest_pos]);
		printed[smallest_pos]++;
		return (1);
	}
	return (0);
}

void	format_and_print(const char *env_var)
{
	char	*name;
	char	*equal;
	char	*value;
	char	*copy;

	copy = ft_strdup_calloc(env_var);
	equal = ft_strchr(copy, '=');
	if (!equal)
		printf("declare -x %s\n", copy);
	else
	{
		*equal = '\0';
		name = copy;
		value = equal + 1;
		printf("declare -x %s=\"%s\"\n", name, value);
	}
	free(copy);
}
