/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:36:42 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/28 23:58:54 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_redirs(t_redir *redirs)
{
	const char	*red_type[] = {"REDIR_NONE", "REDIR_IN", "REDIR_OUT",
		"REDIR_APPEND", "REDIR_HERE"};

	printf("\tredirs:\n");
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
	printf("\tenv_tmp:\n");
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
	printf("\targs:\n");
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
		printf("CMD %i\n", i);
		printf("\tcmd_name:  %s\n", cmd->cmd_name);
		ft_print_args(cmd->args);
		ft_print_env_tmp(cmd->env_tmp);
		ft_print_redirs(cmd->redirs);
		i++;
		cmd = cmd->next;
	}
}
