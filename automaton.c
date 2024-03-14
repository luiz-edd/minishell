

#include "minishell.h"
#define NULL_CHAR 106

int	get_next_state(int state, int column)
{
	static int true_table[9][11] = {{4, 2, 3, 6, 104, 103, 1, 0, 106, 7, 5},
									{200, 200, 200, 200, 200, 200, 100, 200,
										200, 200, 200},
									{201, 101, 201, 201, 201, 201, 201, 201,
										201, 201, 201},
									{203, 203, 102, 203, 203, 203, 203, 203,
										203, 203, 203},
									{4, 202, 202, 8, 202, 202, 202, 202, 202, 7,
										5},
									{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4},
									{4, 202, 202, 105, 202, 202, 202, 202, 202,
										7, 5},
									{7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7},
									{4, 4, 4, 300, 4, 4, 4, 4, 4, 4, 4}};
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
	if (num >= 200 && num < 300)
		return (1);
	return (0);
}

int	is_weird_state(int num)
{
	if (num >= 300)
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

char	*get_type_str(int type)
{
	if (type == OR)
		return ("OR");
	if (type == APPEND)
		return ("APPEND");
	if (type == HERE_DOC)
		return ("HERE_DOC");
	if (type == CLOSE_BRACKET)
		return ("CLOSE_BRACKET");
	if (type == OPEN_BRACKET)
		return ("OPEN_BRACKET");
	if (type == AND)
		return ("AND");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == WORD)
		return ("WORD");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	return ("TYPE NOT FOUND");
}

void	automaton(char *str, t_token **token_list, int start, int state)
{
	int		i;
	char	*value;
	int		size;

	i = 0;
	size = ft_strlen(str) + 1;
	while (i < size)
	{
		if (state == 0)
			start = i;
		state = get_next_state(state, get_column(str[i]));
		if (is_end_state(state) && state != NULL_CHAR)
		{
			if (is_back_state(state))
				i--;
			if (is_weird_state(state))
			{
				state = WORD;
				i -= 2;
			}
			value = ft_substr(str, start, (i - start) + 1);
			ft_lstadd_back_token(token_list, ft_lstnew_token(value, state));
			state = 0;
		}
		i++;
	}
}

void	lexer(char *str)
{
	t_token	*token_lst;
	t_token	*aux;

	token_lst = NULL;
	automaton(str, &token_lst, 0, 0);
	aux = token_lst;
	while (aux)
	{
		ft_printf("{%s, %s}\n", aux->value, get_type_str(aux->type));
		aux = aux->next;
	}
}

// https://automatonsimulator.com/#%7B%22type%22%3A%22DFA%22%2C%22dfa%22%3A%7B%22transitions%22%3A%7B%22start%22%3A%7B%22%7C%22%3A%22s0%22%2C%22%3E%22%3A%22s3%22%2C%22%3C%22%3A%22s6%22%2C%22%26%22%3A%22s12%22%2C%22(%22%3A%22s16%22%2C%22)%22%3A%22s17%22%2C%22s%22%3A%22start%22%2C%22%5C%22%22%3A%22s18%22%2C%22'%22%3A%22s20%22%2C%22o%22%3A%22s14%22%7D%2C%22s0%22%3A%7B%22%7C%22%3A%22s1%22%2C%22o%22%3A%22s2%22%7D%2C%22s3%22%3A%7B%22%3E%22%3A%22s4%22%2C%22o%22%3A%22s5%22%7D%2C%22s6%22%3A%7B%22%3C%22%3A%22s7%22%2C%22o%22%3A%22s8%22%7D%2C%22s12%22%3A%7B%22%26%22%3A%22s13%22%2C%22w%22%3A%22s14%22%2C%22o%22%3A%22s15%22%2C%22%5C%22%22%3A%22s18%22%2C%22'%22%3A%22s20%22%7D%2C%22s14%22%3A%7B%22W%22%3A%22s14%22%2C%22o%22%3A%22s15%22%2C%22%5C%22%22%3A%22s18%22%2C%22'%22%3A%22s20%22%2C%22%26%22%3A%22s9%22%7D%2C%22s18%22%3A%7B%22%5C%22%22%3A%22s14%22%2C%22o%22%3A%22s18%22%7D%2C%22s20%22%3A%7B%22'%22%3A%22s14%22%2C%22o%22%3A%22s20%22%7D%2C%22s9%22%3A%7B%22o%22%3A%22s14%22%2C%22%26%22%3A%22s10%22%7D%7D%2C%22startState%22%3A%22start%22%2C%22acceptStates%22%3A%5B%22s1%22%2C%22s2%22%2C%22s4%22%2C%22s5%22%2C%22s7%22%2C%22s8%22%2C%22s13%22%2C%22s15%22%2C%22s16%22%2C%22s17%22%5D%7D%2C%22states%22%3A%7B%22start%22%3A%7B%7D%2C%22s0%22%3A%7B%22top%22%3A21.466659545898438%2C%22left%22%3A18.466659545898438%2C%22displayId%22%3A%22s1%22%7D%2C%22s3%22%3A%7B%22top%22%3A17.916656494140625%2C%22left%22%3A415.91668701171875%2C%22displayId%22%3A%22s2%22%7D%2C%22s6%22%3A%7B%22top%22%3A90.91665649414062%2C%22left%22%3A397.91668701171875%2C%22displayId%22%3A%22s3%22%7D%2C%22s12%22%3A%7B%22top%22%3A274.90000915527344%2C%22left%22%3A199.89999389648438%2C%22displayId%22%3A%22s6%22%7D%2C%22s16%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A491.99998474121094%2C%22left%22%3A66%2C%22displayId%22%3A104%7D%2C%22s17%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A408.99998474121094%2C%22left%22%3A0%2C%22displayId%22%3A103%7D%2C%22s18%22%3A%7B%22top%22%3A442.99998474121094%2C%22left%22%3A327%2C%22displayId%22%3A%22s5%22%7D%2C%22s20%22%3A%7B%22top%22%3A582.6999969482422%2C%22left%22%3A294.5%2C%22displayId%22%3A%22s7%22%7D%2C%22s14%22%3A%7B%22top%22%3A417.8000030517578%2C%22left%22%3A580.7999877929688%2C%22displayId%22%3A%22s4%22%7D%2C%22s1%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A6.75%2C%22left%22%3A204.75%2C%22displayId%22%3A100%7D%2C%22s2%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A97.83332824707031%2C%22left%22%3A129.83331298828125%2C%22displayId%22%3A%22200*%22%7D%2C%22s4%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A17.916656494140625%2C%22left%22%3A664.9166870117188%2C%22displayId%22%3A101%7D%2C%22s5%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A84.91665649414062%2C%22left%22%3A617.9166870117188%2C%22displayId%22%3A%22201*%22%7D%2C%22s7%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A164%2C%22left%22%3A594%2C%22displayId%22%3A102%7D%2C%22s8%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A258.9166717529297%2C%22left%22%3A624.9166870117188%2C%22displayId%22%3A%22203*%22%7D%2C%22s13%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A237.6999969482422%2C%22left%22%3A378.29998779296875%2C%22displayId%22%3A105%7D%2C%22s15%22%3A%7B%22isAccept%22%3Atrue%2C%22top%22%3A178%2C%22left%22%3A382%2C%22displayId%22%3A%22202*%22%7D%2C%22s9%22%3A%7B%22top%22%3A494.99998474121094%2C%22left%22%3A775%2C%22displayId%22%3A%22s8%22%7D%2C%22s10%22%3A%7B%22top%22%3A339.99998474121094%2C%22left%22%3A920%2C%22displayId%22%3A%22300**%22%7D%7D%2C%22transitions%22%3A%5B%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%7C%22%2C%22stateB%22%3A%22s0%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%3E%22%2C%22stateB%22%3A%22s3%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%3C%22%2C%22stateB%22%3A%22s6%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s12%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22(%22%2C%22stateB%22%3A%22s16%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22)%22%2C%22stateB%22%3A%22s17%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22s%22%2C%22stateB%22%3A%22start%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22%5C%22%22%2C%22stateB%22%3A%22s18%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22'%22%2C%22stateB%22%3A%22s20%22%7D%2C%7B%22stateA%22%3A%22start%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s0%22%2C%22label%22%3A%22%7C%22%2C%22stateB%22%3A%22s1%22%7D%2C%7B%22stateA%22%3A%22s0%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s2%22%7D%2C%7B%22stateA%22%3A%22s3%22%2C%22label%22%3A%22%3E%22%2C%22stateB%22%3A%22s4%22%7D%2C%7B%22stateA%22%3A%22s3%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s5%22%7D%2C%7B%22stateA%22%3A%22s6%22%2C%22label%22%3A%22%3C%22%2C%22stateB%22%3A%22s7%22%7D%2C%7B%22stateA%22%3A%22s6%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s8%22%7D%2C%7B%22stateA%22%3A%22s12%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s13%22%7D%2C%7B%22stateA%22%3A%22s12%22%2C%22label%22%3A%22w%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s12%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s15%22%7D%2C%7B%22stateA%22%3A%22s12%22%2C%22label%22%3A%22%5C%22%22%2C%22stateB%22%3A%22s18%22%7D%2C%7B%22stateA%22%3A%22s12%22%2C%22label%22%3A%22'%22%2C%22stateB%22%3A%22s20%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22W%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s15%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22%5C%22%22%2C%22stateB%22%3A%22s18%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22'%22%2C%22stateB%22%3A%22s20%22%7D%2C%7B%22stateA%22%3A%22s14%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s9%22%7D%2C%7B%22stateA%22%3A%22s18%22%2C%22label%22%3A%22%5C%22%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s18%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s18%22%7D%2C%7B%22stateA%22%3A%22s20%22%2C%22label%22%3A%22'%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s20%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s20%22%7D%2C%7B%22stateA%22%3A%22s9%22%2C%22label%22%3A%22o%22%2C%22stateB%22%3A%22s14%22%7D%2C%7B%22stateA%22%3A%22s9%22%2C%22label%22%3A%22%26%22%2C%22stateB%22%3A%22s10%22%7D%5D%2C%22bulkTests%22%3A%7B%22accept%22%3A%22%22%2C%22reject%22%3A%22%22%7D%7D
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

// treat like a word:	;	&	`	\		[	#	~	% 	\"	\' \0	$

// test ;	&			[	#	~	% 	\"	\' \0	$ | || > >> < << && ( )
// ./minishell "test ;       &                       [ #     ~
// %       \'\' \0 $ | || > >> < << && ( )"

// echo oi""cat' 'ave>>||""&cao&& $ "" '' >>>| || > >> < << && ( )