/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:27:43 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/21 17:08:07 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token *list)
{
	t_token	*current;
	t_tree_node	*root;

	current = list;
	while (current)
	{
		if (check_syntax(current) == FAILURE)
			return (FAILURE);
		current = current->next;
	}
	root = build_execution_tree(list);
	if (root == NULL)
		return (FAILURE);
	print2D(root);
	return (SUCCESS);
}

int	check_syntax(t_token *current)
{
	if (current->type == AND || current->type == OR || current->type == PIPE)
		return (check_control_operator_rule(current));
	else if (current->type >= REDIR_APPEND && current->type <= REDIR_OUT)
		return (check_redirect_rule(current));
	else if (current->type == OPEN_PAREN || current->type == CLOSE_PAREN)
		return (check_parenthesis_rule(current));
	return (SUCCESS);
}

int	check_control_operator_rule(t_token *token)
{
	if (token->prev == NULL || token->prev->type <= PIPE)
		return (syntax_error(token->value));
	if (token->next == NULL || token->next->type <= PIPE)
		return (syntax_error(token->value));
	return (SUCCESS);
}

int	check_redirect_rule(t_token *token)
{
	if (token->next == NULL || token->next->type != WORD)
		return (syntax_error(token->value));
	return (SUCCESS);
}

int	check_parenthesis_rule(t_token *token)
{
	if (token->type == OPEN_PAREN)
	{
		if (token->prev != NULL && token->prev->type > OPEN_PAREN)
			return (syntax_error(token->value));
		if (token->next == NULL || token->next->type <= PIPE)
			return (syntax_error(token->value));
	}
	else if (token->type == CLOSE_PAREN)
	{
		if (token->prev == NULL || (token->prev->type != WORD
				&& token->prev->type != CLOSE_PAREN))
			return (syntax_error(token->value));
		if (token->next != NULL && (token->next->type == WORD))
			return (syntax_error(token->value));
	}
	return (SUCCESS);
}
