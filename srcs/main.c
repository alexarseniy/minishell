/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:44:20 by olarseni          #+#    #+#             */
/*   Updated: 2025/07/08 17:57:31 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{
	char	*cmd;

	(void)argc, (void)argv;
	while(1)
	{
		cmd = readline("minishell> ");
		add_history(cmd);
		printf("Comando: %s\n", cmd);
		rl_on_new_line();
		free(cmd);
		cmd = NULL;
	}
	rl_clear_history();
	return (0);
}
