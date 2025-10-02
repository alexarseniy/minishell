/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:06:16 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 03:44:40 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delquote_args(t_sh *sh, t_cmd *cmd)
{
	char	*aux_str;
	t_args	*aux;

	aux_str = NULL;
	aux = cmd->args;
	if (!sh || sh->err || !cmd)
		return ;
	while (!sh->err && aux)
	{
		if (ft_has_quotes(aux->value))
		{
			aux_str = ft_delquotes(aux->value);
			free(aux->value);
			aux->value = aux_str;
		}
		aux = aux->next;
	}
}

void	delquote_env(t_sh *sh, t_cmd *cmd)
{
	char	*aux_str;
	t_env	*aux;

	aux_str = NULL;
	aux = cmd->env_tmp;
	if (!sh || sh->err || !cmd)
		return ;
	while (!sh->err && aux)
	{
		if (ft_has_quotes(aux->value))
		{
			aux_str = ft_delquotes(aux->value);
			free(aux->value);
			aux->value = aux_str;
		}
		if (ft_has_quotes(aux->key))
		{
			aux_str = ft_delquotes(aux->key);
			free(aux->key);
			aux->key = aux_str;
		}
		aux = aux->next;
	}
}

void	delquote_redirs(t_sh *sh, t_cmd *cmd)
{
	char	*aux_str;
	t_redir	*aux;

	aux_str = NULL;
	aux = cmd->redirs;
	if (!sh || sh->err || !cmd)
		return ;
	while (!sh->err && aux)
	{
		if (ft_has_quotes(aux->file))
		{
			aux_str = ft_delquotes(aux->file);
			free(aux->file);
			aux->file = aux_str;
		}
		aux = aux->next;
	}
}

void	delquote_cmd_name(t_sh *sh, t_cmd *cmd)
{
	char	*aux_str;

	aux_str = NULL;
	if (!sh || sh->err || !cmd)
		return ;
	if (!sh->err && ft_has_quotes(cmd->cmd_name))
	{
		aux_str = ft_delquotes(cmd->cmd_name);
		free(cmd->cmd_name);
		cmd->cmd_name = aux_str;
	}
}

void	ft_delquote(t_sh *shell)
{
	t_cmd				*cmd;
	int					i;
	const t_f_delquotes	f[] = {delquote_args, delquote_env,
		delquote_redirs, delquote_cmd_name, NULL};

	if (!shell || !shell->cmd_lst || shell->err)
		return ;
	cmd = shell->cmd_lst;
	while (cmd)
	{
		i = 0;
		while (!shell->err && f[i])
			f[i++](shell, cmd);
		cmd = cmd->next;
	}
	printf("\033[1m \033[38;5;222m");
	printf("\n--------------------------------------------------------------");
	printf("\n|%42s%19s\n", "CMD nodes after delquote", "|");
	printf("--------------------------------------------------------------\n");
	printf("\033[0m");
	printf("\033[38;5;180m");
	ft_print_cmd(shell->cmd_lst);
	printf("\033[0m");
}
