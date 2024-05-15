/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:16:36 by leduard2          #+#    #+#             */
/*   Updated: 2024/04/30 15:59:40 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_collect_mem(path);
		printf("%s\n", path);
		return (SUCCESS);
	}
	else
		return (handle_error("pwd"));
}
