/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/17 21:12:51 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*list;

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
		printf("You typed: %s\n", line);
		lexer(line, &list);
		parser(list);
		print_list(list);
		free_list(list);
		free(line);
	}
	return (0);
}

void	free_list(t_token *list)
{
	t_token	*current;
	t_token	*next;

	current = list;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
