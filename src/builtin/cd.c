/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:57:59 by leduard2          #+#    #+#             */
/*   Updated: 2024/04/30 15:58:23 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd precisa mudar a variavel da env (PWD e OLDPWD)
int	execute_cd(t_token *cmd)
{
	char	**args;

	if (token_lst_get_size(cmd) > 2)
		return (!!write(STDERR_FILENO, "cd: too many arguments\n", 23));
	args = get_cmd_and_args(cmd);
	if (!args[1] || !ft_strcmp(args[1], "~"))
		return (change_to_home());
	return (change_dir(args[1]));
}

int	change_to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home)
	{
		if (chdir(home) == -1)
			return (handle_error(home));
		return (SUCCESS);
	}
	else
		return (!!write(STDERR_FILENO, "cd: HOME not set\n", 18));
}

int	change_dir(char *path)
{
	char	*work_dir;

	work_dir = getcwd(NULL, 4096);
	if (!work_dir)
		return (handle_error("cd"));
	ft_collect_mem(work_dir);
	if (check_access(path) == FAILURE)
		return (FAILURE);
	if (chdir(path) == -1)
		return (handle_error(path));
	return (SUCCESS);
}

int	check_access(char *path)
{
	if (access(path, F_OK))
		return (!!ft_fprintf(STDERR_FILENO, "cd: %s: no such file or\
 directory\n", path));
	else if (access(path, R_OK))
		return (!!ft_fprintf(STDERR_FILENO, "cd: %s: permission denied\n",
				path));
	return (SUCCESS);
}
