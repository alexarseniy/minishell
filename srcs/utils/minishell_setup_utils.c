/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_setup_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:18:36 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 04:08:48 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setup_shell(t_sh *shell, int argc, char **argv, char *envp[])
{
	if (!shell || !argv || !envp)
		return (ERROR);
	shell->cmd_lst = NULL;
	shell->env = NULL;
	shell->input = NULL;
	shell->here = NULL;
	shell->tkn = NULL;
	shell->err_wrap = ft_get_wrappers();
	shell->err = NONE;
	shell->last_exit_status = 0;
	shell->err = ft_set_interactive_cmd_mode(shell, argc, argv);
	if (shell->err)
		return (shell->err);
	shell->err = ft_create_envp(shell, envp);
	return (shell->err);
}

int	ft_set_interactive_cmd_mode(t_sh *shell, int argc, char **argv)
{
	char	*mode;

	if (!shell || !argv)
		return (ERROR);
	if (argc < 2)
		shell->interactive_mode = 1;
	else
	{
		mode = argv[1];
		if (ft_strncmp(mode, "-c", ft_strlen(mode)))
			return (ERR_INPUT);
		else
			shell->interactive_mode = 0;
	}
	return (0);
}

int	ft_create_envp(t_sh *shell, char *envp[])
{
	if (!shell || !envp)
		return (ERROR);
	shell->env = ft_arr_to_env(envp);
	if (!shell->env)
		return (ERR_ENV);
	return (NONE);
}

const t_err_wrap	*ft_get_wrappers(void)
{
	static const t_err_wrap	wrappers[] = {wrap_lexer, wrap_parser,
		wrap_expand, wrap_delquote, wrap_heredoc, wrap_execute, NULL};

	return (wrappers);
}

void	ft_get_input(t_sh *shell)
{
	const char	*prompt = "\033[38;5;101mminishell: \033[0m";

	shell->input = readline(prompt);
	add_history(shell->input);
	rl_on_new_line();
	if (!shell->input)
	{
		shell->err = ERR_INPUT;
		return ;
	}
}
