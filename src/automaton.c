

#include "minishell.h"

#define END_STATE 99
#define BACK_STATE 98

int	**get_true_table(void)
{
	static int	true_table[5][4] = {{2, 5, 3, 200}, {201, 101, 101, 101}, {4, 4,
			-2, -1}, {4, 4, 202, -1}, {102, 5, 102, 102}};

	return (true_table);
}

int	get_state(int state, int column)
{
	int	**true_table;

	true_table = get_true_table();
	return (true_table[state, column]);
}

int	get_column(char c)
{
	if (c = '>')
		return (0);
	if (c = '\"')
		return (2);
	if (c = '\0')
		return (3);
	if (ft_isalnum((c)))
		return (1);
}

int	is_end_state(int num)
{
	if (num >= 100 && num <= 1000)
		return (1);
	return (0);
}

int	is_back_state(int num)
{
	if (num >= 100 && num < 200)
		return (1);
	return (0);
}

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

// echo>"hello"
t_list	automaton(char *str, t_list **token_list)
{
	int		i;
	int		column;
	int		start;
	int		state;
	char	*value_aux;

	i = 0;
	start = 0;
	state = 0;
	while (str[i])
	{
		column = get_column(str[i]);
		state = get_state(state, column);
		if (is_end_state(state))
		{
			if (is_back_state(state))
				--i;
			value_aux = ft_substr(str[start], start, i - start);
			ft_lstadd_back(token_list, ft_lstnew((void *)create_token(value_aux,
						state)));
			start = i;
		}
		else if (state = -1)
		{
			// fatal error;
		}
		if (state = 1 && str[i] == ' ')
			start = i + 1;
		else
			start++;
		i++;
	}
}

t_list	get_token_list(char *str)
{
	t_list	token_list;
}

void	lexer(char *str)
{
	get_token_list(str);
}