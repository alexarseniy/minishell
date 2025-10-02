/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_add_components.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:45:29 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 02:49:04 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_add_redir(t_sh *sh, t_cmd *cmd, t_token *tkn, char *n_tkn_value)
{
	t_redir	*new;

	new = NULL;
	if (tkn->type == TKN_REDIR_IN)
		new = ft_new_redir(n_tkn_value, REDIR_IN);
	else if (tkn->type == TKN_REDIR_OUT)
		new = ft_new_redir(n_tkn_value, REDIR_OUT);
	else if (tkn->type == TKN_REDIR_APPEND)
		new = ft_new_redir(n_tkn_value, REDIR_APPEND);
	else if (tkn->type == TKN_REDIR_HERE)
		new = ft_new_redir(n_tkn_value, REDIR_HERE);
	if (!new)
	{
		sh->err = ERR_PARSER;
		return ;
	}
	ft_redir_addback(&(cmd->redirs), new);
}

void	ft_cmd_add_assign(t_sh *sh, t_cmd *cmd, t_token *tkn)
{
	t_env	*result;
	char	**aux;

	aux = ft_split(tkn->value, '\0');
	result = ft_arr_to_env(aux);
	if (!result)
	{
		sh->err = ERR_PARSER;
		return ;
	}
	ft_set_env(&cmd->env_tmp, result->key, result->value);
	free(result->key);
	free(result->value);
	result->key = NULL;
	result->value = NULL;
	free(result);
	free(*aux);
	*aux = NULL;
	free(aux);
}

static t_args	*ft_create_new_arg(t_sh *sh, t_cmd *cmd, t_token *tkn)
{
	t_args	*new;

	new = ft_calloc(sizeof(t_args), 1);
	if (!new)
		return (sh->err = ERR_PARSER, NULL);
	new->next = NULL;
	new->value = ft_strdup(tkn->value);
	if (!new->value)
	{
		sh->err = ERR_PARSER;
		free(new);
		return (NULL);
	}
	else
		ft_args_addback(&(cmd->args), new);
	return (new);
}

void	ft_cmd_add_word(t_sh *sh, t_cmd *cmd, t_token *tkn)
{
	if (!cmd->cmd_name)
	{
		cmd->cmd_name = ft_strdup(tkn->value);
		if (!cmd->cmd_name)
			sh->err = ERR_PARSER;
	}
	else
	{
		if (!ft_create_new_arg(sh, cmd, tkn))
		{
			sh->err = ERR_PARSER;
			return ;
		}
	}
}

void	ft_cmd_addtkn(t_sh *sh, t_cmd *cmd, t_token *tkn)
{
	if (ft_is_redir(tkn))
		ft_cmd_add_redir(sh, cmd, tkn, tkn->next->value);
	else if (tkn->type == TKN_ASSIGN)
		ft_cmd_add_assign(sh, cmd, tkn);
	else if (tkn->type == TKN_WORD)
		ft_cmd_add_word(sh, cmd, tkn);
}
