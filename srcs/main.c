/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:44:20 by olarseni          #+#    #+#             */
/*   Updated: 2025/07/12 17:39:03 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	init_shell(t_shell *sh, char *envp[])
{
	(void)sh, (void)envp;
	sh = malloc(sizeof(sh) + 1);
	if (!sh || env_init(&sh->env, envp))
		return (-1);
	return (0);
}

int	start_shell(t_shell *sh)
{
	sh->usr_input = "start";
	while (sh->usr_input && sh->usr_input[0])
	{
		sh->usr_input = readline("minishell");
		printf("Command == %s\n", sh->usr_input);
		add_history(sh->usr_input);
		rl_on_new_line();
	}
	rl_clear_history();
	return (0);

}

int	free_shell(t_shell *sh)
{
	free(shell);
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	t_shell sh;

	(void)argc, (void)argv;
	if (!init_shell(&sh, envp))
		start_shell(&sh);
	free_shell(&sh);
	return (sh.status);
}
