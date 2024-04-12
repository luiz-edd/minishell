/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:16:36 by leduard2          #+#    #+#             */
/*   Updated: 2024/04/12 16:35:02 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(void)
{
	char *path;

	path = getcwd(NULL, 4096);
	ft_collect_mem(path);
	if (path)
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		return (SUCCESS);
	}
	return (handle_error("minishell: pwd"));
}