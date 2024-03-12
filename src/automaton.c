

#include "minishell.h"

#define END_STATE 99
#define BACK_STATE 98

int	**get_true_table(void)
{
	static int	true_table[5][4] = {
		{2, 5, 3, 200}, 
		{201, 101, 101, 101}, 
		{4, 4,
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

// https://automatonsimulator.com/#%7B%22type%22%3A%22DFA%22%2C%22dfa%22%3A%7B%22transitions%22%3A%7B%22start%22%3A%7B%22%7C%22%3A%22s0%22%2C%22%3E%22%3A%22s3%22%2C%22%3C%22%3A%22s6%22%2C%22%26%22%3A%22s12%22%2C%22W%22%3A%22s14%22%2C%22(%22%3A%22s16%22%2C%22)%22%3A%22s17%22%2C%22s%22%3A%22start%22%7D%2C%22s0%22%3A%7B%22%7C%22%3A%22s1%22%2C%22o%22%3A%22s2%22%7D%2C%22s3%22%3A%7B%22%3E%22%3A%22s4%22%2C%22o%22%3A%22s5%22%7D%2C%22s6%22%3A%7B%22%3C%22%3A%22s7%22%2C%22o%22%3A%22s8%22%7D%2C%22s12%22%3A%7B%22%26%22%3A%22s13%22%2C%22o%22%3A%22s14%22%7D%2C%22s14%22%3A%7B%22W%22%3A%22s14%22%2C%22o%22%3A%22s15%22%2C%22%26%22%3A%22s12%22%2C%22%5C%22%22%3A%22s18%22%2C%22'%22%3A%22s20%22%7D%2C%22s18%22%3A%7B%22%5C%22%22%3A%22s14%22%2C%22o%22%3A%22s19%22%7D%2C%22s19%22%3A%7B%22o%22%3A%22s19%22%2C%22%5C%22%22%3A%22s14%22%7D%2C%22s20%22%3A%7B%22'%22%3A%22s14%22%2C%22o%22%3A%22s21%22%7D%2C%22s21%22%3A%7B%22o%22%3A%22s21%22%2C%22'%22%3A%22s14%22%7D%7D%2C%22startState%22%3A%22start%22%2C%22acceptStates%22%3A%5B%22s1%22%2C%22s2%22%2C%22s4%22%2C%22s5%22%2C%22s7%22%2C%22s8%22%2C%22s13%22%2C%22s15%22%2C%22s16%22%2C%22s17%22%5D%7D%2C%22states%22%3A%7B%22start%22%3A%7B%7D%2C%22s0%22%3A%7B%22top%22%3A17.666656494140625%2C%22left%22%3A13.666671752929688%2C%22displayId%22%3A%22s0%22%7D%2C%22s3%22%3A%7B%22top%22%3A18.916656494140625%2C%22left%22%3A415.91668701171875%2C%22displayId%22%3A%22s3%22%7D%2C%22s6%22%3A%7B%22top%22%3A90.91665649414062%2C%22left%22%3A397.91668701171875%2C%22displayId%22%3A%22s6%22%7D%2C%22s12%22%3A%7B%22top%22%3A372.99998474121094%2C%22left%22%3A166%2C%22displayId%22%3A%22s12%22%7D%2C%22s14%22%3A%7B%22top%22%3A356.99998474121094%2C%22left%22%3A529%2C%22displayId%22%3A%22s14%22%7D%2C%22s16%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A491.99998474121094%2C%22left%22%3A66%2C%22displayId%22%3A%22s16%22%7D%2C%22s17%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A408.99998474121094%2C%22left%22%3A0%2C%22displayId%22%3A%22s17%22%7D%2C%22s1%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A6.75%2C%22left%22%3A204.75%2C%22displayId%22%3A%22s1%22%7D%2C%22s2%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A69.83332824707031%2C%22left%22%3A188.83331298828125%2C%22displayId%22%3A%22s2*%22%7D%2C%22s4%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A17.916656494140625%2C%22left%22%3A622.9166870117188%2C%22displayId%22%3A%22s4*%22%7D%2C%22s5%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A83.91665649414062%2C%22left%22%3A568.9166870117188%2C%22displayId%22%3A%22s5%22%7D%2C%22s7%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A164%2C%22left%22%3A594%2C%22displayId%22%3A%22s7*%22%7D%2C%22s8%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A250.9166717529297%2C%22left%22%3A563.9166870117188%2C%22displayId%22%3A%22s8%22%7D%2C%22s13%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A505.99998474121094%2C%22left%22%3A303%2C%22displayId%22%3A%22s13%22%7D%2C%22s15%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A148%2C%22left%22%3A426%2C%22displayId%22%3A%22s15*%22%7D%2C%22s18%22%3A%7B%22top%22%3A264.99998474121094%2C%22left%22%3A897%2C%22displayId%22%3A%22s18%22%7D%2C%22s20%22%3A%7B%22top%22%3A552.9999847412109%2C%22left%22%3A472%2C%22displayId%22%3A%22s20%22%7D%2C%22s19%22%3A%7B%22top%22%3A451.99998474121094%2C%22left%22%3A826%2C%22displayId%22%3A%22s19%22%7D%2C%22s21%22%3A%7B%22top%22%3A544.9999847412109%2C%22left%22%3A701%2C%22displayId%22%3A%22s21%22%7D%7D%2C%22transitions%22%3A%5B%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%7C%22%2C%22stateB%22%3A%22s0%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%3E%22%2C%22stateB%22%3A%22s3%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%3C%22%2C%22stateB%22%3A%22s6%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s12%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22W%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22(%22%2C%22stateB%22%3A%22s16%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22)%22%2C%22stateB%22%3A%22s17%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22s%22%2C%22stateB%22%3A%22start%22%7D%2C%7B%22stateA%22%3A%22s0%22%2C%22label%22%3A%22%7C%22%2C%22stateB%22%3A%22s1%22%7D%2C%7B%22stateA%22%3A%22s0%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s2%22%7D%2C%7B%22stateA%22%3A%22s3%22%2C%22label%22%3A%22%3E%22%2C%22stateB%22%3A%22s4%22%7D%2C%7B%22stateA%22%3A%22s3%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s5%22%7D%2C%7B%22stateA%22%3A%22s6%22%2C%22label%22%3A%22%3C%22%2C%22stateB%22%3A%22s7%22%7D%2C%7B%22stateA%22%3A%22s6%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s8%22%7D%2C%7B%22stateA%22%3A%22s12%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s13%22%7D%2C%7B%22stateA%22%3A%22s12%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22W%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s15%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s12%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22%5C%22%22%2C%22stateB%22%3A%22s18%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22'%22%2C%22stateB%22%3A%22s20%22%7D%2C%7B%22stateA%22%3A%22s18%22%2C%22label%22%3A%22%5C%22%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s18%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s19%22%7D%2C%7B%22stateA%22%3A%22s19%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s19%22%7D%2C%7B%22stateA%22%3A%22s19%22%2C%22label%22%3A%22%5C%22%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s20%22%2C%22label%22%3A%22'%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s20%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s21%22%7D%2C%7B%22stateA%22%3A%22s21%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s21%22%7D%2C%7B%22stateA%22%3A%22s21%22%2C%22label%22%3A%22'%22%2C%22stateB%22%3A%22s14%22%7D%5D%2C%22bulkTests%22%3A%7B%22accept%22%3A%22%22%2C%22reject%22%3A%22%22%7D%7D
// tratar final da string ao encotnrar caracter \0
// Variables
// |
// || 
// >
// >>
// <
// <<
// &&
// (
// )
// spaces
// word {special case quotes}

// treat like a word:	;	&	`	\	 [	#	~	% 	"	' \0	$
