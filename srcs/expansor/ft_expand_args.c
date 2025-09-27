/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:05:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 23:05:46 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_args(t_sh *shell, t_cmd *cmd)
{
	t_args	*args;
	char	*aux;

	if (!shell || !cmd)
		return ;
	args = cmd->args;
	while (args)
	{
		if (ft_has_expand(args->value))
		{
			aux - ft_expand(args->value);
			free(args->value);
			args->value = aux;
			if (!args->value)
			{
				shell->err = ERR_EXPAND;
				return ;
			}
		}
		args = args->next;
	}
}
