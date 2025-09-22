/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:25:24 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/22 04:10:07 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_env(t_sh *sh)
{
	t_env	*env;
	t_env	*aux;

	env = sh->env;
	while (env)
	{
		aux = env->next;
		free(env->key);
		free(env->value);
		env->key = NULL;
		env->value = NULL;
		env->next = NULL;
		free(env);
		env = aux;
	}
	env = NULL;
}

void	ft_clean(t_sh *sh)
{
	ft_clean_tkns(sh);
	ft_clean_here(sh);
	ft_clean_cmd(sh);
	free(sh->input);
	sh->tkn = NULL;
	sh->here = NULL;
	sh->cmd_lst = NULL;
	sh->input = NULL;
	sh->err = 0;
}

void	ft_clean_all(t_sh *sh)
{
	ft_clean(sh);
	ft_clean_env(sh);
	sh->env = NULL;
	rl_clear_history();
}

void	ft_free_parts(t_token *tkn)
{
	t_tkn_parts	*aux;

	if (!tkn)
		return ;
	while (tkn->parts)
	{
		aux = tkn->parts->next;
		free(tkn->parts->value);
		tkn->parts->value = NULL;
		tkn->parts->next = NULL;
		free(tkn->parts);
		tkn->parts = aux;
	}
	tkn->parts = NULL;
}

void	ft_clean_tkns(t_sh *sh)
{
	t_token	*aux;

	if (!sh)
		return ;
	while (sh->tkn)
	{
		aux = sh->tkn->next;
		free(sh->tkn->value);
		ft_free_parts(sh->tkn);
		sh->tkn->next = NULL;
		sh->tkn->value = NULL;
		sh->tkn->parts = NULL;
		free(sh->tkn);
		sh->tkn = aux;
	}
	sh->tkn = NULL;
}
