/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 04:04:12 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/22 04:11:46 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_operator(t_token **tkn, char *input, int *i, t_sh *sh)
{
	int		j;
	t_token	*new;
	char	*value;

	j = *i;
	if (ft_is_operator(input[*i + 1]))
		j++;
	value = ft_substr(input, *i, j - *i + 1);
	if (!value)
	{
		sh->err = ERR_HANDLE_OP_SUBSTR;
		return ;
	}
	new = ft_tkn_new(value, ft_get_tkn_type(value), NULL);
	if (!new)
	{
		sh->err = ERR_HANDLE_OP_TKN_NEW;
		free(value);
		return ;
	}
	ft_tkn_addback(tkn, new);
	free(value);
	*i = j + 1;
}

static int	ft_find_end_word(char *input, int i)
{
	int	in_squote;
	int	in_dquote;

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
		else if (!in_dquote && !in_squote && ft_isspace(input[i]))
			break ;
		else if (!in_dquote && !in_squote && ft_is_operator(input[i]))
			break ;
		i++;
	}
	return (i - 1);
}

void	ft_handle_word(t_token **tkn, char *input, int *i, t_sh *sh)
{
	int		j;	
	t_token	*new;
	char	*value;

	j = *i;
	j = ft_find_end_word(input, *i);
	value = ft_substr(input, *i, j - *i + 1);
	if (!value)
	{
		sh->err = ERR_HANDLE_WORD_SUBSTR;
		return ;
	}
	new = ft_tkn_new(value, TKN_WORD, NULL);
	if (!new)
	{
		sh->err = ERR_HANDLE_WORD_TKN_NEW;
		free(value);
		return ;
	}
	ft_tkn_addback(tkn, new);
	free(value);
	*i = j + 1;
}
