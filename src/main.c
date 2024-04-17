/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/17 17:55:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	t_token		*list;
	t_tree_node	*root;
	int			pid;
	int			exit_status;

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
					// if (is_builtin(root->cmd) && there_is_only_one_root)
					// 	execute_builtin(root->cmd);
					// else
					// {
					pid = fork();
					if (pid == 0)
						executor(root);
					else
						waitpid(pid, &exit_status, 0);
					// }
				}
			}
			free(line);
			create_heredoc_file(DELETE);
		}
	}
	return (SUCCESS);
}
