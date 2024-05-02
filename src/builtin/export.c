/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:12:58 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/02 14:44:50 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *content)
{
	char	*value;

	value = ft_strchr(search_env_lst(content), '=');
	if (value)
		return (value + 1);
	return (value);
}

void	export(t_token *cmd)
{
	char **args;
	char *content;
	int i;

	i = 0;
	args = get_cmd_and_args(cmd);
	if(ft_arrstr_len(args) == 1)
	{
		//print export;
	}
	content = search_env_lst(*args);
	if (content)
		get_env_key(content);
}