/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/07 16:02:14 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *line;
	
	while (42)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		else
			add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			printf("exit\n");
			free(line);
			exit(0);
		}
		else
		{
			printf("You typed: %s\n", line);
			free(line);
		}
	}
	return (0);	
}
