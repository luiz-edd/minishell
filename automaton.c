

#include "minishell.h"

#define END_STATE 99
#define BACK_STATE 98

int	get_next_state(int state, int column)
{
	int true_table[8][11] = {
		{4, 2, 3, 6, 104, 103, 1, 0, 106, 4, 4},
		{200, 200, 200, 200, 200, 200, 100, 200, 200, 200, 200},
		{101, 201, 101, 101, 101, 101, 101, 101, 101, 101, 101},
		{102, 102, 203, 102, 102, 102, 102, 102, 102, 102, 102},
		{4, 202, 202, 202, 202, 202, 202, 202, 202, 7, 5},
		{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4},
		{4, 4, 4, 105, 4, 4, 4, 4, 4, 4, 4},
		{7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7}};
	return (true_table[state][column]);
}

int	get_column(char c)
{
	if (c == '>')
		return (1);
	if (c == '<')
		return (2);
	if (c == '&')
		return (3);
	if (c == '(')
		return (4);
	if (c == ')')
		return (5);
	if (c == '|')
		return (6);
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (7);
	if (c == '\0')
		return (8);
	if (c == '\'')
		return (9);
	if (c == '\"')
		return (10);
	return (0); // word
}

int	is_end_state(int num)
{
	if (num >= 100)
		return (1);
	return (0);
}

int	is_back_state(int num)
{
	if (num >= 200)
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
void	automaton(char *str, t_token **token_list)
{
	int		i;
	int		column;
	int		start;
	int		state;
	char	*value_aux;
	int		size;

	i = 0;
	start = 0;
	state = 0;
	size = ft_strlen(str) + 1;
	//0123456
	//echo >> cat<<
	while (i <= size)
	{
		column = get_column(str[i]);
		// ft_printf("%c",str[i]);
		state = get_next_state(state, column);
		if (is_end_state(state) && state != 106)
		{
			if (is_back_state(state))
			{
				value_aux = ft_substr(str, start, i-start);
				i--;
				start = i;
				// ft_pri    cntf("back_state -->");
			}
			else
			{
				value_aux = ft_substr(str, start, (i - start));
				// ft_printf("end_state -->");
				start = i + 1;
			}
			ft_printf("tokem:|%s|                   state|%i|\n", value_aux, state);
			ft_lstadd_back_token(token_list, ft_lstnew_token(value_aux, state));
			state = 0;
		}
		if (state == 0 && str[i] == ' ')
			start = i + 1;
		i++;
	}
}

void	lexer(char *str)
{
	t_token	*token_lst;
	t_token	*aux;

	token_lst = NULL;
	automaton(str, &token_lst);
	aux = token_lst;
	// while (aux)
	// {
	// 	ft_printf("{%s, %i}\n", aux->value, aux->type);
	// 	aux = aux->next;
	// }
}

// https://automatonsimulator.com/#%7B%22type%22%3A%22DFA%22%2C%22dfa%22%3A%7B%22transitions%22%3A%7B%22start%22%3A%7B%220%22%3A%22s10%22%2C%22%7C%22%3A%22s0%22%2C%22%3E%22%3A%22s3%22%2C%22%3C%22%3A%22s6%22%2C%22%26%22%3A%22s12%22%2C%22W%22%3A%22s14%22%2C%22(%22%3A%22s16%22%2C%22)%22%3A%22s17%22%2C%22s%22%3A%22start%22%7D%2C%22s0%22%3A%7B%22%7C%22%3A%22s1%22%2C%22o%22%3A%22s2%22%7D%2C%22s3%22%3A%7B%22%3E%22%3A%22s4%22%2C%22o%22%3A%22s5%22%7D%2C%22s6%22%3A%7B%22%3C%22%3A%22s7%22%2C%22o%22%3A%22s8%22%7D%2C%22s12%22%3A%7B%22%26%22%3A%22s13%22%2C%22o%22%3A%22s14%22%7D%2C%22s14%22%3A%7B%22W%22%3A%22s14%22%2C%22o%22%3A%22s15%22%2C%22%26%22%3A%22s12%22%2C%22%5C%22%22%3A%22s18%22%2C%22'%22%3A%22s20%22%7D%2C%22s18%22%3A%7B%22%5C%22%22%3A%22s14%22%2C%22o%22%3A%22s18%22%7D%2C%22s20%22%3A%7B%22'%22%3A%22s14%22%2C%22o%22%3A%22s20%22%7D%7D%2C%22startState%22%3A%22start%22%2C%22acceptStates%22%3A%5B%22s1%22%2C%22s2%22%2C%22s4%22%2C%22s5%22%2C%22s7%22%2C%22s8%22%2C%22s13%22%2C%22s15%22%2C%22s16%22%2C%22s17%22%2C%22s10%22%5D%7D%2C%22states%22%3A%7B%22start%22%3A%7B%7D%2C%22s10%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A569.9999847412109%2C%22left%22%3A188%2C%22displayId%22%3A%22106%22%7D%2C%22s0%22%3A%7B%22top%22%3A17.666656494140625%2C%22left%22%3A13.666671752929688%2C%22displayId%22%3A%22s0%22%7D%2C%22s3%22%3A%7B%22top%22%3A17.916656494140625%2C%22left%22%3A415.91668701171875%2C%22displayId%22%3A%22s2%22%7D%2C%22s6%22%3A%7B%22top%22%3A90.91665649414062%2C%22left%22%3A397.91668701171875%2C%22displayId%22%3A%22s3%22%7D%2C%22s12%22%3A%7B%22top%22%3A372.99998474121094%2C%22left%22%3A165%2C%22displayId%22%3A%22s6%22%7D%2C%22s14%22%3A%7B%22top%22%3A356.99998474121094%2C%22left%22%3A529%2C%22displayId%22%3A%22s4%22%7D%2C%22s16%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A491.99998474121094%2C%22left%22%3A66%2C%22displayId%22%3A%22104%22%7D%2C%22s17%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A408.99998474121094%2C%22left%22%3A0%2C%22displayId%22%3A%22103%22%7D%2C%22s1%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A6.75%2C%22left%22%3A204.75%2C%22displayId%22%3A%22100%22%7D%2C%22s2%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A97.83332824707031%2C%22left%22%3A129.83331298828125%2C%22displayId%22%3A%22200*%22%7D%2C%22s4%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A17.916656494140625%2C%22left%22%3A664.9166870117188%2C%22displayId%22%3A%22201*%22%7D%2C%22s5%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A84.91665649414062%2C%22left%22%3A617.9166870117188%2C%22displayId%22%3A%22101%22%7D%2C%22s7%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A164%2C%22left%22%3A594%2C%22displayId%22%3A%22203*%22%7D%2C%22s8%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A250.9166717529297%2C%22left%22%3A563.9166870117188%2C%22displayId%22%3A%22102%22%7D%2C%22s13%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A505.99998474121094%2C%22left%22%3A303%2C%22displayId%22%3A%22105%22%7D%2C%22s15%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A158%2C%22left%22%3A425%2C%22displayId%22%3A%22202*%22%7D%2C%22s18%22%3A%7B%22top%22%3A332.99998474121094%2C%22left%22%3A852%2C%22displayId%22%3A%22s5%22%7D%2C%22s20%22%3A%7B%22top%22%3A552.9999847412109%2C%22left%22%3A471%2C%22displayId%22%3A%22s7%22%7D%7D%2C%22transitions%22%3A%5B%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%220%22%2C%22stateB%22%3A%22s10%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%7C%22%2C%22stateB%22%3A%22s0%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%3E%22%2C%22stateB%22%3A%22s3%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%3C%22%2C%22stateB%22%3A%22s6%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s12%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22W%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22(%22%2C%22stateB%22%3A%22s16%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22)%22%2C%22stateB%22%3A%22s17%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22s%22%2C%22stateB%22%3A%22start%22%7D%2C%7B%22stateA%22%3A%22s0%22%2C%22label%22%3A%22%7C%22%2C%22stateB%22%3A%22s1%22%7D%2C%7B%22stateA%22%3A%22s0%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s2%22%7D%2C%7B%22stateA%22%3A%22s3%22%2C%22label%22%3A%22%3E%22%2C%22stateB%22%3A%22s4%22%7D%2C%7B%22stateA%22%3A%22s3%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s5%22%7D%2C%7B%22stateA%22%3A%22s6%22%2C%22label%22%3A%22%3C%22%2C%22stateB%22%3A%22s7%22%7D%2C%7B%22stateA%22%3A%22s6%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s8%22%7D%2C%7B%22stateA%22%3A%22s12%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s13%22%7D%2C%7B%22stateA%22%3A%22s12%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22W%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s15%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s12%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22%5C%22%22%2C%22stateB%22%3A%22s18%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22'%22%2C%22stateB%22%3A%22s20%22%7D%2C%7B%22stateA%22%3A%22s18%22%2C%22label%22%3A%22%5C%22%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s18%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s18%22%7D%2C%7B%22stateA%22%3A%22s20%22%2C%22label%22%3A%22'%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s20%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s20%22%7D%5D%2C%22bulkTests%22%3A%7B%22accept%22%3A%22%22%2C%22reject%22%3A%22%22%7D%7D
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

// treat like a word:	;	&	`	\		[	#	~	% 	"	' \0	$
