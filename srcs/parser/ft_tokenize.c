/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:04:29 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/04 17:17:31 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief main flow that transform the users input into a linked list of tokens
 * to do so, the flow follows these steps:
 *		-> extrat the next available word
 *		-> add the word to the token list
 *		-> update the input cmd pointer
 *		-> set types for all words
 *		-> set parts for all words
 * @param cmd	input seted by the user
 * @return	Returns a token list
 * @retval	t_token *token_lst
 * @retval	NULL if something went wrong.
 */
t_token	*ft_tokenize(char *cmd)
{
	t_token	*token_lst;
	char	*word;

	token_lst = NULL;
	while (cmd)
	{
		word = ft_tkn_get_word(cmd);
		if (!word || ft_tkn_addback(&token_lst, ft_tkn_new(word)))
			return (ft_free_tokens(token_lst), NULL);
		ft_tkn_next_word(&cmd);
	}
	if (ft_tkn_set_tkn_type(&token_lst) || ft_tkn_set_tkn_parts(&token_lst))
		return (ft_free_tokens(token_lst), NULL);
	return (token_lst);
}

static char	*ft_tkn_get_word(const char *cmd)
{
	char	*word;
	char	*start;
	char	*end;
	bool	is_quoted;

	start = cmd;
	end = cmd;
	while (end && *end && (*end != ft_isspace(*end) || is_quted))
	{
		
	}
	return (ft_substr(start, 0, end - start - 1));
}

void	ft_free_tokens(t_tokens *tokens)
{
	t_token	*aux;
	while (token)
	{
		aux = tokens;
		tokens = tokens->next;
		aux->next = NULL;
		free(aux->token);
		free(aux);
		aux = NULL;
	}
}
