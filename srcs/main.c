/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:52:54 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/30 12:14:58 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_main_loop(t_env *env)
{
	(void)env;
	while (true)
	{
		readline("\33[38;5;65mminishell:\33[0m ");
		rl_on_new_line();

	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc, (void)argv;
	env = ft_init_env(envp);
	ft_setup_signals();
	ft_main_loop(env);
	ft_free_env(env);
	return (0);
}
