/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_cmd_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:05:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 23:05:46 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_name(t_sh *shell, t_cmd *cmd)
{
    char    *cmd_name;
	char	*aux;

	if (!shell || !shell->cmd_lst)
		return ;
    cmd_name = cmd->cmd_name;
	if (ft_has_expand(cmd_name))
	{
		aux - ft_expand(cmd_name);
		free(cmd_name);
		cmd_name = aux;
		if (!cmd_name)
		{
			shell->err = ERR_EXPAND;
			return ;
		}
	}
}
