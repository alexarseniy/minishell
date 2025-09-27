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

void	ft_expansor(t_sh *shell)
{
	t_cmd		*cmd;
	int			i;
	const void	(*f)(t_sh *, t_cmd *)[] = {expand_args, expand_env,
		expand_redirs, expand_cmd_name, NULL};

	if (!shell || !shell->cmd_lst)
		return ;
	cmd = shell->cmd_lst;
	while (start)
	{
		i = 0;
		while (!shell->err && f[i])
			f[i++](shell, cmd);
	}
}
