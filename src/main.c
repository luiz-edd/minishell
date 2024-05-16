/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/16 16:59:03 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	leave_program(void);

// investigar como retornar os atributos do terminal
// tcgetattr();
int	main(void)
{
	char		*line;
	t_token		*list;
	t_tree_node	*root;

	init_environ();
	while (42)
	{
		if (setup_signal_handler(main_signal_handler) != SUCCESS)
			return (signal_error());
		list = NULL;
		line = readline("minishell> ");
		if (!line)
			break ;
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
	return (leave_program());
}

int	leave_program(void)
{
	free_env();
	write(STDOUT_FILENO, "exit\n", 5);
	return (SUCCESS);
}
