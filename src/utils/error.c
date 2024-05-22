/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:21:11 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/22 18:10:03 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token)
{
	ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n",
		token);
	return (set_exit_status(SYNTAX_ERROR));
}

int	throw_error(char *cmd_path)
{
	if (*cmd_path == '\0')
		cmd_path = " ";
	if (access(cmd_path, X_OK) == -1 && !access(cmd_path, F_OK))
	{
		ft_fprintf(STDERR_FILENO, "%s: Permission denied\n", cmd_path);
		return (126);
	}
	else if ((*cmd_path == '.' || ft_strchr(cmd_path, '/')) && !access(cmd_path,
			F_OK))
	{
		ft_fprintf(STDERR_FILENO, "%s: Is a directory\n", cmd_path);
		return (126);
	}
	else if (errno == 2 || !getenv("PATH"))
	{
		ft_fprintf(STDERR_FILENO, "%s: No such file or directory\n", cmd_path);
		return (127);
	}
	else
		return (!!write(STDERR_FILENO, "minishell: unexpected error\n", 28));
}

int	handle_error(char *message)
{
	if (*message == '\0')
		message = " ";
	ft_fprintf(STDERR_FILENO, "%s: %s\n", message, strerror(errno));
	ft_free_memory();
	return (!!errno);
}

int	signal_error(void)
{
	ft_fprintf(STDERR_FILENO, "minishell: failed to install signal handler\n");
	return (FAILURE);
}
