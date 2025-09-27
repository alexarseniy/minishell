/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:05:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 23:05:46 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    expand_redirs(t_sh *shell, t_cmd *cmd)
{
	t_redir *redirs;
	char	*aux;

	if (!shell || !cmd)
		return ;
	redirs = cmd->redirs;
	while (redirs)
	{
		if (ft_has_expand(redirs->file))
		{
			aux - ft_expand(redirs->file);
			free(redirs->file);
			redirs->file = aux;
			if (!redirs->file)
			{
				shell->err = ERR_EXPAND;
				return ;
			}
		}
		redirs = redirs->next;
	}
}