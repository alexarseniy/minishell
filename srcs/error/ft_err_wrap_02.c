/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_wrap_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:32:29 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 23:02:52 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	wrap_execute(t_sh *shell)
{
	if (!shell)
		return (ERROR);
	if (shell->err)
		return (shell->err);
	ft_execute(shell);
	return (shell->err);
}
