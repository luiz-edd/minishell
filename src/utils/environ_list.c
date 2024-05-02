/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:18:05 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/02 15:08:10 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**get_env_lst(void)
{
	static t_list	*env;

	return (&env);
}
void	add_env_lst(char *content)
{
	ft_lstadd_back(get_env_lst(), ft_lstnew((void *)content));
}

void	init_env_lst(void)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = __environ;
	while (tmp[i])
		ft_lstadd_back(get_env_lst(), ft_lstnew((void *)(tmp[i++])));
}

void	free_env_lst(void)
{
	ft_lstclear(get_env_lst, &free);
}
char	*search_env_lst(char *content)
{
	t_list *env;

	env = get_env_lst();
	while (env)
	{
		if (ft_strncmp((char *)env->content, content, ft_strlen(content)) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}