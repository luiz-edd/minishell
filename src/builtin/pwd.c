/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:16:36 by leduard2          #+#    #+#             */
/*   Updated: 2024/04/15 18:23:40 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 4096);
	ft_collect_mem(path);
	if (path)
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		return (SUCCESS);
	}
	return (handle_error("minishell: pwd"));
}
