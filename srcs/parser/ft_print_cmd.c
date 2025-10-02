/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:36:42 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 01:39:00 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_redirs(t_redir *redirs)
{
	const char	*red_type[] = {"REDIR_NONE", "REDIR_IN", "REDIR_OUT",
		"REDIR_APPEND", "REDIR_HERE"};

	printf("\t\033[38;5;179mredirs:\033[0m\n");
	printf("\t\t");
	while (redirs)
	{
		printf("{%s, %s}; ", redirs->file, red_type[redirs->type]);
		redirs = redirs->next;
	}
	printf("\n");
}

static void	ft_print_env_tmp(t_env *env_tmp)
{
	printf("\t\033[38;5;179menv_tmp:\033[0m\n");
	printf("\t\t");
	while (env_tmp)
	{
		printf("%s=%s; ", env_tmp->key, env_tmp->value);
		env_tmp = env_tmp->next;
	}
	printf("\n");
}

static void	ft_print_args(t_args *args)
{
	printf("\t\033[38;5;179margs:\033[0m\n");
	printf("\t\t");
	while (args)
	{
		printf("%s; ", args->value);
		args = args->next;
	}
	printf("\n");
}

void	ft_print_cmd(t_cmd *cmd)
{
	int			i;

	i = 0;
	while (cmd)
	{
		printf("\033[1m\033[38;5;179mCMD %i\033[0m\n", i);
		printf("\t\033[38;5;179mcmd_name:\033[0m  %s\n", cmd->cmd_name);
		ft_print_args(cmd->args);
		ft_print_env_tmp(cmd->env_tmp);
		ft_print_redirs(cmd->redirs);
		i++;
		cmd = cmd->next;
	}
	printf("\033[0m");
}
