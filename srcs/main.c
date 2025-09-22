/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:28:27 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/22 04:15:20 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	main_cmd(t_sh *shell, char *input)
{
	const t_err_wrap	*f = shell->err_wrap;

	if (!shell)
		return (ERROR);
	if (!input)
		return (ERR_NO_INPUT);
	shell->input = ft_strdup(input);
	if (!shell->input)
		return (ERR_STRDUP_ERR);
	while (!shell->err && *f)
	{
		shell->err = (*f)(shell);
		f++;
	}
	return (shell->err);
}

static void	main_loop(t_sh *shell, int argc, char **argv)
{
	int	i;

	if (!shell->interactive_mode)
	{
		if (argc > 2 && argv[2] && main_cmd(shell, argv[2]))
			ft_exit_err(shell);
		return ;
	}
	while (1)
	{
		//ft_sig_setup();
		ft_get_input(shell);
		i = 0;
		while (!shell->err && shell->err_wrap[i])
			shell->err_wrap[i++](shell);
		if (shell->err)
			ft_print_err(shell);
		ft_clean(shell);
	}
}

int	main(int argc, char **argv, char *envp[])
{
	t_sh	shell;

	ft_setup_shell(&shell, argc, argv, envp);
	if (shell.err)
		ft_exit_err(&shell);
	main_loop(&shell, argc, argv);
	return (ft_print_err(&shell), ft_clean_all(&shell), shell.err);
}
