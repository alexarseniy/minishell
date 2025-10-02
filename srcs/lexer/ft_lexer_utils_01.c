/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 04:00:24 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 01:31:46 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tkn(t_token *tkn)
{
	const char	*type[] = {"TKN_NONE", "TKN_REDIR_IN", "TKN_REDIR_OUT",
		"TKN_REDIR_APPEND", "TKN_REDIR_HERE", "TKN_PIPE", "TKN_WORD",
		"TKN_ASSIGN_WORD"};
	int			i;

	i = 0;
	while (tkn)
	{
		printf("\033[38;5;179m\033[1mTOKEN %i\033[0m", i);
		printf("\t\033[38;5;179m|-> VALUE: \033[0m%s\n", tkn->value);
		printf("\t\033[38;5;179m|-> TYPE: \033[0m%s\n", type[tkn->type]);
		tkn = tkn->next;
		i++;
	}
}

int	ft_is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	ft_is_valid_op(char *input, int i)
{
	char	op;
	char	op2;
	int		count;

	op = input[i];
	count = 0;
	while (input[i] && ft_is_operator(input[i]))
	{
		count++;
		i++;
	}
	if (count >= 3)
		return (0);
	if (count == 2)
		op2 = input[i - count + 1];
	if (count == 2 && op != op2)
		return (0);
	if (count == 2 && op == '|' && op2 == '|')
		return (0);
	return (1);
}

t_tkn_type	ft_get_tkn_type(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (TKN_REDIR_HERE);
	if (!ft_strncmp(str, ">>", 2))
		return (TKN_REDIR_APPEND);
	if (str[0] == '<')
		return (TKN_REDIR_IN);
	if (str[0] == '>')
		return (TKN_REDIR_OUT);
	if (str[0] == '|')
		return (TKN_PIPE);
	return (TKN_NONE);
}
