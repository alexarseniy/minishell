/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:52:54 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/12 22:09:30 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_main_loop(t_env *env, char **argv)
{
	char	*cmd;

	(void)env;
	cmd = NULL;
	while (true)
	{
		if (!ft_strcmp(argv[1], "-c"))
			cmd = ft_strdup(argv[2]);
		else
			cmd = readline(PROMPT);
		add_history(cmd);
		rl_on_new_line();
		// parse cmd
		// execute cmd
		free(cmd);
	}
	rl_clear_history();
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc, (void)argv;
	env = ft_init_env(envp);
	ft_setup_signals();
	ft_main_loop(env, argv);
	ft_free_env(env);
	return (0);
}
