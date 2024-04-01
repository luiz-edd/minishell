/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:29:32 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/01 19:47:55 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// lembrar de deletar heredoc file na saida do programa
void	create_heredoc_file(t_token *token)
{
	static int	i;
	int			fd;
	char		*line;
	char		*file_name;

	file_name = ft_strjoin("/tmp/.heredoc", ft_itoa(i++));
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(STDERR_FILENO, "failed to create heredoc", 25);
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, token->value) == SUCCESS)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(token->value);
	token->value = file_name;
}
