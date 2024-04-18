/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/18 19:01:50 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	t_token		*list;
	t_tree_node	*root;

	while (42)
	{
		list = NULL;
		line = readline("minishell> ");
		if (!line)
			printf("exit\n");
		else if (*line != '\0')
		{
			add_history(line);
			if (lexer(line, &list) == SUCCESS)
			{
				if (parser(list, &root) == SUCCESS)
				{
					if (last_exit_status_holder(executor(root)))
						wait_for_all_children();
				}
			}
			free(line);
			create_heredoc_file(DELETE);
			ft_free_memory();
		}
	}
	return (SUCCESS);
}
