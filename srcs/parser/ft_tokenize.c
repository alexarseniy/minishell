/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:04:29 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/12 22:21:18 by olarseni         ###   ########.fr       */
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
	while (cmd && *cmd)
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

/** 
 * @brief indentify a word and return a new string for this word
 * Definition for the WORD:
 *		-> Any alphanumeric combination separated by spaces or other words
 *		-> Any char combination inside the quotes
 *		-> Any combination of alphanumeric + quoted chars
 *		-> One of the following symbols >, >>, <, <<, |
 *		-> Assign like "VAR1=value"
 * The words can stay together or separated by spaces
 * @param char *cmd	Users input
 * @return	Returns a word
 * @retval	char *word
 * @retval	NULL if something went wrong
 */
static char	*ft_tkn_get_word(const char *cmd)
{
	char		*start;
	t_tkn_type	tkn;
	bool		is_quoted;

	if (!cmd)
		return (NULL);
	is_queted = false;
	while (ft_isspace(*cmd))
		cmd++;
	start = cmd;
	tkn = ft_get_tkn_type(cmd);
	if (tkn == HEREDOC || tkn == REDIR_APPEND)
		return (ft_substr(cmd, 0, 2));
	if (tkn == PIPE || tkn == REDIR_IN || tkn == REDIR_OUT)
		return (ft_substr(cmd, 0, 1));
	if (*cmd == '\'' || *cmd == '\"')
		is_quoted = true;
	while (*cmd && !ft_isspace(*cmd) && (is_quoted || ft_isalnum(*cmd)
			|| (*cmd == '=')))
	{
		if (*cmd == '\'' || *cmd == '\"')
			is_quoted ^= true;
		cmd++;
	}
	return (ft_substr(start, 0, cmd - start - 1));
}

static t_tkn_type	ft_get_tkn_type(char *str)
{
	if (!str)
		return (NONE);
	if (*str == '>' && *(str + 1) && *(str + 1) == '>')
		return (REDIR_APPEND);
	if (*str == '<' && *(str + 1) && *(str + 1) == '<')
		return (HEREDOC);
	if (*str == '<')
		return (REDIR_IN);
	if (*str == '>')
		return (REDIR_OUT);
	if (*str == '|')
		return (PIPE);
	if (*str == '\"' || *str == '\'')
		return (WORD);
	if (ft_isalpha(*str) && ft_strchr(str, '=') && (!ft_strchr(str, '\'')
			|| !ft_strchr(str, '\"')))
		return (ASSIGNMENT);
	if (ft_isalnum(*str))
		return (WORD);
	else
		return (NONE);
}

/** TODO
 */
static void	ft_tkn_next_word(char **cmd)
{
}

/** TODO
*/
int	ft_tkn_addback(ft_token **token_lst, ft_token *token_new)
{
	t_token	*first_tkn;

	if (!token_new || !token_lst)
		return (1);
	first_tkn = *token_lst;
	while (*token_lst && (*token_lst)->next)
		(*token_lst) = (*token_lst)->next;
	if (!(*token_lst))
		(*token_lst) = token_new;
	else
		(*token_lst)->next = token_new;
	(*token_lst) = first_tkn;
	return (0);
}

/** TODO
*/
t_token	*ft_tkn_new(char *word)
{
	t_token	*new_tkn;

	if (!word)
		return (NULL);
	new_tkn = ft_calloc(sizeof(t_token), 1);
	if (!new_tkn)
		return (NULL);
	new_tkn->value = word;
	new_tkn->tkn_parts = NULL;
	new_tkn->type = NONE;
	new_tkn->next = NULL;
	return (new_tkn);
}

/** TODO
 *
 */
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
