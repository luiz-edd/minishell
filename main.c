/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/13 17:00:40 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	if(argc)
	{}
	lexer(argv[1]);
	// char	*line;

	// while (42)
	// {
	// 	line = readline("minishell> ");
	// 	if (!line)
	// 	{
	// 		printf("exit\n");
	// 		break ;
	// 	}
	// 	else
	// 		add_history(line);
	// 	if (ft_strncmp(line, "exit", 4) == 0)
	// 	{
	// 		printf("exit\n");
	// 		free(line);
	// 		exit(0);
	// 	}
	// 	else
	// 	{
	// 		printf("You typed: %s\n", line);
	// 		lexer(line);
	// 		free(line);
	// 	}
	// }
	return (0);
}
