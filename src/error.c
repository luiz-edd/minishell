/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:21:11 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/17 20:00:00 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	return (FAILURE);
}

int	handle_error(char *message)
{
	if (errno)
	{
		perror(message);
		return (errno);
	}
	else
	{
		dprintf(STDERR_FILENO, "%s\n", message);
		return (FAILURE);
	}
}
