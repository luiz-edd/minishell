/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:57:59 by leduard2          #+#    #+#             */
/*   Updated: 2024/04/12 17:45:30 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(char *path)
{
	if (access(path, F_OK))
		return (handle_error("cd: no such file or directory"));
	else if (access(path, R_OK))
		return (handle_error("cd: permission denied"));
	return (SUCCESS);
}
int	change_dir(char *path)
{
	char	*work_dir;

	work_dir = getcwd(NULL, 4096);
	ft_collect_mem(work_dir);
	if (!work_dir)
	{
		return (handle_error("cd: error retrieving current directory: "
								"getcwd: cannot access parent directories: "
								"no such file or directory"));
	}
	// if (!check_access(path))
	// 	return (handle_error(work_dir));
	ft_printf("path: %s\n", path);
	if (!chdir(path))
		return (SUCCESS);
	else
		return (handle_error(path));
	return (SUCCESS);
}

int	change_to_home(void)
{
	char	*home;

	home = getenv("HOME");
	ft_collect_mem(home);
	if (home)
	{
		ft_printf("%s\n\n", home);
		if (!chdir(home))
			return (SUCCESS);
		else
			return (handle_error(home));
	}
	else
		return (handle_error("cd: HOME not set"));
}
//atualizar getenv
int	execute_cd(t_token *cmd)
{
	char **args;

	if (token_lst_get_size(cmd) > 2)
		return (handle_error("minishell: too many arguments"));
	args = get_cmd_and_args(cmd);
	if (!ft_strcmp(args[1], "~") || !args[1])
		return (change_to_home());
	return (change_dir(args[1]));
}