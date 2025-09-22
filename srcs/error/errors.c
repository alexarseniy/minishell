/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:18:48 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/22 05:23:50 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	ft_exit_err(t_sh *shell)
{
	if (!shell)
	{
		shell->err = 1;
		ft_print_err(shell);
		exit(1);
	}
	else if (shell->err)
		ft_print_err(shell);
	ft_clean_all(shell);
	exit(shell->err);
}

void	ft_print_err(t_sh *shell)
{
	const char	*start = "ERROR: ";
	const char	*str[] = {"OK", "Unknown error", "Error setup shell",
		"Input invalid", "No input", "Error exec ft_strdup",
		"Error in lexer process", "Error in env proces",
		"Error in parser process", "Error in expand process",
		"Error in delquote process", "Error in heredoc process",
		"Error in execute process", "Forbidden character in input",
		"Has unclosed quotes", "Error in handle op substr",
		"Error in handle op new token", "Invalid operator or word",
		"Error in handle word substr", "Error in handle word new token",
		"Invalid syntax"};

	if (!shell->err)
		return ;
	ft_putstr_fd(CRED, 2);
	ft_putstr_fd(start, 2);
	ft_putstr_fd(str[shell->err], 2);
	ft_putendl_fd(RESET, 2);
}
