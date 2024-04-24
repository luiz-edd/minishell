/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/24 17:30:32 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_tree_node **root)
{
	if (set_exit_status(execute(*root)))
		wait_for_all_children();
}
int	main(void)
{
	char		*line;
	t_token		*list;
	t_tree_node	*root;

	save_std_fd();
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
					executor(&root);
			}
			free(line);
			create_heredoc_file(DELETE);
			ft_free_memory();
			revert_fds();
		}
	}
	return (SUCCESS);
}
