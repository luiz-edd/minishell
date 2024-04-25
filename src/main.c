/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/25 20:48:04 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char				*line;
	t_token				*list;
	t_tree_node			*root;

	save_std_fd();
	while (42)
	{
		if (setup_signal_handler(main_signal_handler) != SUCCESS)
			continue ;
		list = NULL;
		line = readline("minishell> ");
		if (!line)
			return (SUCCESS + write(STDOUT_FILENO, "exit\n", 5) - 5);
		else if (*line != '\0')
		{
			add_history(line);
			if (lexer(line, &list) == SUCCESS)
			{
				if (parser(list, &root) == SUCCESS)
					executor(line, &root);
			}
		}
	}
	return (SUCCESS);
}
