/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:57:59 by leduard2          #+#    #+#             */
/*   Updated: 2024/04/29 18:23:23 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cd sozinho está dando segfault
// cd precisa mudar a variavel da env (PWD e OLDPWD)
// cd ~ está dando segfault
int	execute_cd(t_token *cmd)
{
	char	**args;

	if (token_lst_get_size(cmd) > 2)
		return (handle_error("cd: too many arguments"));
	args = get_cmd_and_args(cmd);
	if (!ft_strcmp(args[1], "~") || !args[1])
		return (change_to_home());
	return (change_dir(args[1]));
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

int	change_dir(char *path)
{
	char	*work_dir;

	work_dir = getcwd(NULL, 4096);
	ft_collect_mem(work_dir);
	if (!work_dir)
		return (handle_error("cd"));
	if (!check_access(path))
		return (handle_error(work_dir));
	printf("path: %s\n", path);
	if (!chdir(path))
		return (SUCCESS);
	else
		return (handle_error(path));
	return (SUCCESS);
}

int	check_access(char *path)
{
	if (access(path, F_OK))
		return (handle_error("cd: no such file or directory"));
	else if (access(path, R_OK))
		return (handle_error("cd: permission denied"));
	return (SUCCESS);
}
