/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_wrap_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:19:23 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 23:02:06 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	wrap_lexer(t_sh *shell)
{
	if (!shell)
		return (ERROR);
	if (shell->err)
		return (shell->err);
	ft_lexer(shell);
	return (shell->err);
}

t_error	wrap_parser(t_sh *shell)
{
	if (!shell)
		return (ERROR);
	if (shell->err)
		return (shell->err);
	ft_parser(shell);
	return (shell->err);
}

t_error	wrap_expand(t_sh *shell)
{
	if (!shell)
		return (ERROR);
	if (shell->err)
		return (shell->err);
	ft_expand(shell);
	return (shell->err);
}

t_error	wrap_delquote(t_sh *shell)
{
	if (!shell)
		return (ERROR);
	if (shell->err)
		return (shell->err);
	ft_delquote(shell);
	return (shell->err);
}

t_error	wrap_heredoc(t_sh *shell)
{
	if (!shell)
		return (ERROR);
	if (shell->err)
		return (shell->err);
	ft_heredoc(shell);
	return (shell->err);
}
