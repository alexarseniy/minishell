/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:05:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/28 20:43:54 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expansor(t_sh *shell)
{
	t_cmd				*cmd;
	int					i;
	const t_f_expands	f[] = {expand_args, expand_env,
		expand_redirs, expand_cmd_name, NULL};

	if (!shell || !shell->cmd_lst)
		return ;
	cmd = shell->cmd_lst;
	while (cmd)
	{
		i = 0;
		while (!shell->err && f[i])
			f[i++](shell, cmd);
		cmd = cmd->next;
	}
	ft_print_cmd(shell->cmd_lst);
}
