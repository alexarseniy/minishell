/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:33:49 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/22 07:59:24 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_here(t_sh *sh)
{
	t_here	*aux;

	if (!sh)
		return ;
	while (sh->here)
	{
		aux = sh->here->next;
		free(sh->here->del);
		free(sh->here->content);
		sh->here->del = NULL;
		sh->here->content = NULL;
		sh->here->next = NULL;
		free(sh->here);
		sh->here = aux;
	}
	sh->here = NULL;
}

void	ft_free_redirs(t_redir *redirs)
{
	t_redir	*aux;

	if (!redirs)
		return ;
	while (redirs)
	{
		aux = redirs->next;
		free(redirs->file);
		redirs->file = NULL;
		redirs->next = NULL;
		free(redirs);
		redirs = aux;
	}
	redirs = NULL;
}

void	ft_clean_cmd(t_sh *sh)
{
	t_cmd	*aux;

	(void)aux;
	if (!sh)
		return ;
/*	while (sh->cmd_lst)
	{
		aux = sh->cmd_lst->next;
		free(sh->cmd_lst->cmd_name);
		free(sh->cmd_lst->args);
		sh->cmd_lst->cmd_name = NULL;
		sh->cmd_lst->args = NULL;
		sh->cmd_lst->next = NULL;
		ft_free_redirs(sh->cmd_lst->redirs);
		sh->cmd_lst->redirs = NULL;
		free(sh->cmd_lst);
		sh->cmd_lst = aux;
	}
	sh->cmd_lst = NULL;*/
}
