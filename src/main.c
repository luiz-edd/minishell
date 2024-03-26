/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/26 19:41:38 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*list;
	t_tree_node	*root;
	int exit_status;

	while (42)
	{
		list = NULL;
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		else
			add_history(line);
		if (lexer(line, &list) == SUCCESS)
			if (parser(list, &root) == SUCCESS)
				executor(root);
		waitpid(-1, &exit_status, 0);
		free(line);
	}
	return (0);
}
