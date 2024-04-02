/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:29:32 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/02 18:24:55 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checar a questão do eof estar entre aspas
// se existe aspas na função ele tira porém não expande o que estiver no arquivo
// se não tem aspas ele expande (Tanto simples quanto duplas)
int	create_heredoc_file(t_token *token)
{
	static int	i;
	int			fd;
	char		*line;
	char		*file_name;
	int			expand;

	expand = 1;
	if (token == NULL)
		return (delete_heredoc_files(&i));
	file_name = ft_strjoin("/tmp/.heredoc", ft_itoa(i++));
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (write(STDERR_FILENO, "failed to create heredoc", 25));
	if (ft_strchr(token->value, '\"') || ft_strchr(token->value, '\''))
		expand = 0;
	token->value = remove_quotes(token->value);
	printf("token->value: %s\n", token->value);
	while (42)
	{
		line = readline("> ");
		if (ft_strcmp(line, token->value) == SUCCESS)
			break ;
		//if (expand)
			//expand_vars(line);
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

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_dalloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				tmp[j++] = str[i++];
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				tmp[j++] = str[i++];
		}
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}
