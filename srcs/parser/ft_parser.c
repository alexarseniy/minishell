/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:04:58 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/28 23:49:57 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_check_syntax(t_token *tkn)
{
	t_token	*next;

	if (tkn->type == TKN_PIPE)
		return (1);
	next = tkn->next;
	while (tkn)
	{
		if (!next && ft_is_operator(tkn->value[0]))
			return (1);
		if (next && ft_is_operator(tkn->value[0])
			&& ft_is_operator(next->value[0]))
			return (1);
		tkn = next;
		if (tkn)
			next = tkn->next;
	}
	return (0);
}

static int	ft_parser_prechecker(t_sh *sh)
{
	if (!sh)
		return (1);
	if (!sh->tkn)
		return (sh->err = ERR_PARSER, 1);
	if (ft_check_syntax(sh->tkn))
		return (sh->err = ERR_SYNTAX, 1);
	return (0);
}

t_cmd	*ft_parsing(t_sh *sh, t_token *tkn)
{
	t_cmd	*lst;
	t_cmd	*current;

	lst = NULL;
	current = ft_calloc(sizeof(t_cmd), 1);
	if (!current)
		return (sh->err = ERR_PARSER, NULL);
	while (!sh->err && tkn)
	{
		if (tkn->type == TKN_PIPE)
		{
			ft_cmd_addback(&lst, current);
			current = ft_calloc(sizeof(t_cmd), 1);
			if (!current)
				return (sh->err = ERR_PARSER, NULL);
		}
		else
			ft_cmd_addtkn(sh, current, tkn);
		if (ft_is_redir(tkn))
			tkn = tkn->next->next;
		else
			tkn = tkn->next;
	}
	return (ft_cmd_addback(&lst, current), lst);
}

static void	ft_set_assign_words(t_sh *sh, t_token *tkn)
{
	int	flag_word;
	int	flag_redir;

	flag_word = 0;
	flag_redir = 0;
	while (!sh->err && tkn && !flag_word)
	{
		if (!flag_redir && (tkn->value[0] == '>' || tkn->value[0] == '<'))
			flag_redir = 1;
		else if (!flag_redir && tkn->type == TKN_WORD && (tkn->value[0] == '\''
				|| tkn->value[0] == '"' || !ft_strchr(tkn->value, '=')))
			flag_word = 1;
		else if (!flag_redir && tkn->type == TKN_WORD)
			tkn->type = TKN_ASSIGN;
		else
			flag_redir = 0;
		tkn = tkn->next;
	}
}

void	ft_parser(t_sh *shell)
{
	if (ft_parser_prechecker(shell))
		return ;
	ft_set_assign_words(shell, shell->tkn);
	shell->cmd_lst = ft_parsing(shell, shell->tkn);
	if (shell->err)
		return ;
	ft_print_cmd(shell->cmd_lst);
}
