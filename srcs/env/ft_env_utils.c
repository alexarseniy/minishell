/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 04:10:51 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/29 05:44:29 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>
#include <stdio.h>

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!key || !value)
		return (free(new->key), free(new->value), free(new), NULL);
	return (new);
}

t_env	*ft_lst_last(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_envlst_addback(t_env **lst, t_env *node)
{
	if (!lst || !node)
		return (1);
	if (!*lst)
		*lst = node;
	else
		ft_lst_last(*lst)->next = node;
	return (0);
}

void	ft_free_env(t_env *env)
{
	t_env	*aux;

	while (env)
	{
		free(env->key);
		free(env->value);
		env->key = NULL;
		env->value = NULL;
		aux = env;
		env = env->next;
		free(aux);
	}
}

void	ft_print_env(t_env *lst)
{
	while (lst)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}
