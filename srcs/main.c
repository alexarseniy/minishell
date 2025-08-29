/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:52:54 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/29 06:16:55 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

static void	ft_main_loop(t_env *env)
{
	(void)env;
	return ;
}

static void	ft_setup_signals(void)
{
	return ;
}

static void test_env(t_env *env)
{
	t_env *node;

	node = ft_get_env(env, "USER");
	printf("KEY: %s\nVALUE: %s\n", node->key, node->value);
	ft_set_env(&env, "USER", NULL);
	printf("KEY: %s\nVALUE: %s\n", node->key, node->value);
	ft_set_env(&env, "USER", "");
	printf("KEY: %s\nVALUE: %s\n", node->key, node->value);
	ft_set_env(&env, "USER", "maquina!");
	printf("KEY: %s\nVALUE: %s\n", node->key, node->value);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int	i;

	(void)argc, (void)argv;
	env = ft_init_env(envp);
	char **env_arr = ft_env_to_arr(env);
	test_env(env);
	/*
	i = 0;
	while (env_arr[i])
	{
		printf("%s\n", env_arr[i]);
		i++;
	}
	*/
	i = 0;
	while (env_arr[i])
		free(env_arr[i++]);
	free(env_arr);
	ft_setup_signals();
	ft_main_loop(env);
	ft_free_env(env);
	return (0);
}
