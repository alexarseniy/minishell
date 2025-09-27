/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:05:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 23:05:46 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_env_key(t_sh *shell, t_cmd *cmd)
{
	t_env	*env;
	char	*aux_key;

	if (!shell || !cmd)
		return ;
	env = cmd->env_tmp;
	while (!shell->err && env)
	{
		if (ft_has_expand(env->key))
		{
			aux_key = ft_expand(env->key);
			free(env->key);
			env->key = aux_key;
			if (!aux_key)
			{
				shell->err = ERR_EXPAND;
				return ;
			}
		}
		env = env->next;
	}
}

static void	expand_env_value(t_sh *shell, t_cmd *cmd)
{
	t_env	*env;
	char	*aux_value;

	if (!shell || !cmd)
		return ;
	env = cmd->env_tmp;
	while (env)
	{
		if (ft_has_expand(env->value))
		{
			aux_value = ft_expand(env->value);
			free(env->value);
			env->value = aux_value;
			if (!aux_value)
			{
				shell->err = ERR_EXPAND;
				return ;
			}
		}
		env = env->next;
	}
}

void	expand_env(t_sh *shell, t_cmd *cmd)
{
	if (!shell || !cmd)
		return ;
	ft_expand_env_key(shell, cmd);
	ft_expand_env_value(shell, cmd);
}
