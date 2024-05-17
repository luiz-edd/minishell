/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/17 19:42:21 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_shell(struct termios *term);
char	*init_and_wait_input(struct termios *term, t_token **list);
int		leave_program(int status);

int	main(void)
{
	char					*line;
	t_token					*list;
	t_tree_node				*root;
	static struct termios	term;

	// init_shell(&term);
	init_environ();
	tcgetattr(STDIN_FILENO, &term);
	while (42)
	{
		line = init_and_wait_input(&term, &list);
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
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		reset_for_next_iteration(line);
	}
	return (leave_program(SUCCESS));
}

// int	init_shell(struct termios *term)
// {
// 	init_environ();
// 	(void)term;
// 	// if (tcgetattr(STDIN_FILENO, term) == -1)
// 	// {
// 	// 	write(STDERR_FILENO, "minishell: error getting terminal attributes\n",
// 	// 			46);
// 	// 	return (FAILURE);
// 	// }
// 	return (SUCCESS);
// }

char	*init_and_wait_input(struct termios *term, t_token **list)
{
	char	*line;

	(void)term;
	if (setup_signal_handler(main_signal_handler) != SUCCESS)
	{
		free_env();
		ft_free_memory();
		exit(signal_error());
	}
	// tcsetattr(STDIN_FILENO, TCSANOW, term);
	*list = NULL;
	line = readline("minishell> ");
	return (line);
}

int	leave_program(int status)
{
	// printf("leaving program\n");
	free_env();
	ft_free_memory();
	write(STDOUT_FILENO, "exit\n", 5);
	return (status);
}
