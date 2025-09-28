/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansor_cmd_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:20:59 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/28 23:28:14 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_args(t_sh *shell, t_cmd *cmd)
{
	(void)shell, (void)cmd;
	return ;
}

void	expand_env(t_sh *shell, t_cmd *cmd)
{
	(void)shell, (void)cmd;
	return ;
}

void	expand_redirs(t_sh *shell, t_cmd *cmd)
{
	(void)shell, (void)cmd;
	return ;
}

void	expand_cmd_name(t_sh *shell, t_cmd *cmd)
{
	if (!shell || !cmd)
		return ;
	while (!shell->err && ft_has_expand(cmd->cmd_name))
		cmd->cmd_name = ft_expand(shell, cmd->cmd_name);
}
