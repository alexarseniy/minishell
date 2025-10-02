/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:03:11 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 01:37:32 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_has_unclosed_quotes(char *input)
{
	int	in_squote;
	int	in_dquote;
	int	i;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_squote && !in_dquote)
			in_squote = 1;
		else if (input[i] == '"' && !in_squote && !in_dquote)
			in_dquote = 1;
		else if (in_squote && input[i] == '\'')
			in_squote = 0;
		else if (in_dquote && input[i] == '"')
			in_dquote = 0;
		i++;
	}
	if (in_squote || in_dquote)
		return (1);
	return (0);
}

static int	ft_lexer_prechecker(t_sh *sh)
{
	if (!sh)
		return (1);
	else if (!sh->input)
		return (sh->err = ERR_NO_INPUT, 1);
	else if (ft_has_unclosed_quotes(sh->input))
		return (sh->err = ERR_UNCLOSED_QUOTES, 1);
	return (0);
}

t_token	*ft_tokenize(t_sh *sh, char *input)
{
	int		i;
	t_token	*tkn;

	i = 0;
	tkn = NULL;
	while (!sh->err && input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (ft_is_operator(input[i]) && ft_is_valid_op(input, i))
			ft_handle_operator(&tkn, input, &i, sh);
		else if (!ft_is_operator(input[i]))
			ft_handle_word(&tkn, input, &i, sh);
		else
			sh->err = ERR_INVALID_OP_WORD;
	}
	return (tkn);
}

void	ft_lexer(t_sh *shell)
{
	if (ft_lexer_prechecker(shell))
		return ;
	shell->tkn = ft_tokenize(shell, shell->input);
	if (shell->err)
		return ;
	printf("\033[1m \033[38;5;222m");
	printf("\n--------------------------------------------------------------");
	printf("\n|%35s%26s\n", "Token nodes", "|");
	printf("--------------------------------------------------------------\n");
	printf("\033[0m");
	ft_print_tkn(shell->tkn);
	printf("\033[0m");
}
