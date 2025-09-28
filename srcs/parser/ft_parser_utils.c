/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:34:59 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/28 23:36:37 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_asign(t_token *tkn)
{
	if (tkn->type != TKN_WORD)
		return (0);
	if (tkn->value[0] == '\'' || tkn->value[0] == '\"')
		return (0);
	if (!ft_strchr(tkn->value, '='))
		return (0);
	return (1);
}

int	ft_is_redir(t_token *tkn)
{
	if (tkn->type == TKN_REDIR_IN || tkn->type == TKN_REDIR_OUT)
		return (1);
	if (tkn->type == TKN_REDIR_APPEND || tkn->type == TKN_REDIR_HERE)
		return (1);
	return (0);
}
