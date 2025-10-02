/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:05:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 01:37:16 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expansor(t_sh *shell)
{
	t_cmd				*cmd;
	int					i;
	const t_f_expands	f[] = {expand_args, expand_env,
		expand_redirs, expand_cmd_name, NULL};

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
	printf("\n|%42s%19s\n", "CMD nodes after expansor", "|");
	printf("--------------------------------------------------------------\n");
	printf("\033[0m");
	printf("\033[38;5;180m");
	ft_print_cmd(shell->cmd_lst);
	printf("\033[0m");
}
