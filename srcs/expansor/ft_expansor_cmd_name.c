/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansor_cmd_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:20:59 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 01:42:29 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_args(t_sh *shell, t_cmd *cmd)
{
	t_args	*aux;

	if (!shell || shell->err || !cmd)
		return ;
	aux = cmd->args;
	if (!aux)
		return ;
	while (!shell->err && aux)
	{
		if (!ft_has_expand(aux->value))
			aux = aux->next;
		else
			aux->value = ft_expand(shell, aux->value);
	}
	return ;
}

void	expand_env(t_sh *shell, t_cmd *cmd)
{
	t_env	*aux;

	if (!shell || shell->err || !cmd)
		return ;
	aux = cmd->env_tmp;
	if (!aux)
		return ;
	while (!shell->err && aux)
	{
		if (!ft_has_expand(aux->key) && !ft_has_expand(aux->value))
			aux = aux->next;
		if (aux && ft_has_expand(aux->key))
			aux->key = ft_expand(shell, aux->key);
		if (aux && ft_has_expand(aux->value))
			aux->value = ft_expand(shell, aux->value);
	}
	return ;
}

void	expand_redirs(t_sh *shell, t_cmd *cmd)
{
	t_redir	*aux;

	if (!shell || shell->err || !cmd)
		return ;
	aux = cmd->redirs;
	if (!aux)
		return ;
	while (!shell->err && aux)
	{
		if (aux->type == REDIR_HERE || !ft_has_expand(aux->file))
			aux = aux->next;
		else
			aux->file = ft_expand(shell, aux->file);
	}
	return ;
}

void	expand_cmd_name(t_sh *shell, t_cmd *cmd)
{
	if (!shell || shell->err || !cmd)
		return ;
	while (!shell->err && ft_has_expand(cmd->cmd_name))
		cmd->cmd_name = ft_expand(shell, cmd->cmd_name);
}
