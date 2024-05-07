/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/07 14:51:03 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//!line tem que dar free na env
int	main(void)
{
	char				*line;
	t_token				*list;
	t_tree_node			*root;

	while (42)
	{
		if (setup_signal_handler(main_signal_handler) != SUCCESS)
			return (FAILURE);
		list = NULL;
		line = readline("minishell> ");
		if (!line)
			return (!write(STDOUT_FILENO, "exit\n", 5));
		else if (*line != '\0')
		{
			add_history(line);
			if (lexer(line, &list) == SUCCESS)
			{
				if (parser(list, &root) == SUCCESS)
					set_exit_status(executor(root));
			}
		}
		reset_for_next_iteration(line);
	}
	return (SUCCESS);
}
