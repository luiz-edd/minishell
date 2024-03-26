/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/26 17:58:57 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*list;
	t_tree_node	*root;

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
		free(line);
	}
	return (0);
}
