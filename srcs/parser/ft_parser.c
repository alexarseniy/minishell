/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:04:58 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/25 19:15:17 by olarseni         ###   ########.fr       */
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

t_cmd *ft_cmd_last(t_cmd *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_cmd_addback(t_cmd **lst, t_cmd *new)
{
	t_cmd	*aux;

	if (!lst)
		return ;
	aux = *lst;
	if (!aux)
	{
		*lst = new;
		return ;
	}
	aux = ft_cmd_last(aux);
	aux->next = new;
	return ;
}

t_redir *ft_new_redir(char *value, t_redir_type type)
{
	t_redir	*new;

	if (!value || !type)
		return (NULL);
	new = ft_calloc(sizeof(t_redir), 1);
	if (!new)
		return (NULL);
	new->file = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_redir *ft_redir_last(t_redir *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_redir_addback(t_redir **lst, t_redir *new)
{
	t_redir *aux;

	if (!lst)
		return ;
	aux = *lst;
	if (!aux)
	{
		*lst = new;
		return ;
	}
	aux = ft_redir_last(aux);
	aux->next = new;
}

void	ft_cmd_add_redir(t_sh *sh, t_cmd *cmd, t_token *tkn, char *n_tkn_value)
{
	t_redir *new;

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

t_args *ft_args_last(t_args *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_args_addback(t_args **lst, t_args *new)
{
	t_args *aux;

	if (!lst)
		return ;
	aux = *lst;
	if (!aux)
	{
		*lst = new;
		return ;
	}
	aux = ft_args_last(aux);
	aux->next = new;
}

void	ft_cmd_add_word(t_sh *sh, t_cmd *cmd, t_token *tkn)
{
	t_args	*new;
	if (!cmd->cmd_name)
	{
		cmd->cmd_name = ft_strdup(tkn->value);
		if (!cmd->cmd_name)
			sh->err = ERR_PARSER;
	}
	else
	{
		new = ft_calloc(sizeof(t_args), 1);
		if (!new)
		{
			sh->err = ERR_PARSER;
			return ;
		}
		new->next = NULL;
		new->value = ft_strdup(tkn->value);
		if (!new->value)
		{
			sh->err = ERR_PARSER;
			free(new);
		}
		else
			ft_args_addback(&(cmd->args), new);
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

void	ft_print_cmd(t_cmd *cmd)
{
	const char	*red_type[] = {"REDIR_NONE", "REDIR_IN", "REDIR_OUT", "REDIR_APPEND", "REDIR_HERE"};
	int	i;

	i = 0;
	while (cmd)
	{
		printf("CMD %i\n", i);
		printf("\tcmd_name:  %s\n", cmd->cmd_name);
		printf("\targs:\n");
		printf("\t\t");
		while (cmd->args)
		{
			printf("%s; ", cmd->args->value);
			cmd->args = cmd->args->next;
		}
		printf("\n");
		printf("\tenv_tmp:\n");
		printf("\t\t");
		while (cmd->env_tmp)
		{
			printf("%s=%s; ", cmd->env_tmp->key, cmd->env_tmp->value);
			cmd->env_tmp = cmd->env_tmp->next;
		}
		printf("\n");
		printf("\tredirs:\n");
		printf("\t\t");
		while (cmd->redirs)
		{
			printf("{%s, %s}; ", cmd->redirs->file, red_type[cmd->redirs->type]);
			cmd->redirs = cmd->redirs->next;
		}
		printf("\n");
		i++;
		cmd = cmd->next;
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
