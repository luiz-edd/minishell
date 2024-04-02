/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:29:32 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/02 16:07:08 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checar a questão do eof estar entre aspas
int	create_heredoc_file(t_token *token)
{
	static int	i;
	int			fd;
	char		*line;
	char		*file_name;

	if (token == NULL)
		return (delete_heredoc_files(&i));
	file_name = ft_strjoin("/tmp/.heredoc", ft_itoa(i++));
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (write(STDERR_FILENO, "failed to create heredoc", 25));
	while (42)
	{
		line = readline("> ");
		if (ft_strcmp(line, token->value) == SUCCESS)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	token->value = file_name;
	return (SUCCESS);
}

int	delete_heredoc_files(int *i)
{
	char	*file_name;

	while ((*i) >= 0)
	{
		file_name = ft_strjoin("/tmp/.heredoc", ft_itoa((*i)--));
		unlink(file_name);
	}
	return (SUCCESS);
}
