/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:29:32 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/24 15:26:36 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc_file(t_token *token)
{
	static int	count;
	int			fd;
	char		*file_name;
	int			is_expandable;

	is_expandable = 0;
	if (token == DELETE)
		return (delete_heredoc_files(&count));
	file_name = ft_strjoin("/tmp/.heredoc", ft_itoa(count++));
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (!!write(STDERR_FILENO, "failed to create heredoc", 25));
	if (!ft_strchr(token->value, '\"') && !ft_strchr(token->value, '\''))
		is_expandable = 1;
	token->value = remove_quotes(token->value);
	while (42)
		if (write_input_to_heredoc(fd, token->value, is_expandable) == SUCCESS)
			break ;
	close(fd);
	token->value = file_name;
	return (SUCCESS);
}

int	write_input_to_heredoc(int fd, char *end_condition, int is_expandable)
{
	char		*line;

	line = readline("> ");
	if (ft_strcmp(line, end_condition) == SUCCESS)
		return (SUCCESS);
	if (is_expandable)
		line = expand_vars(line);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (FAILURE);
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
