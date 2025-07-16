/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:39:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/07/16 19:43:46 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "env_core.h"

t_env	*ft_env_new(char *key, char *value, bool alloc)
{
	t_env	*node;

	node = malloc(sizeof(node));
	if (!node)
		return (NULL);
	if (!alloc)
	{
		node->key = ft_strdup(key);
		node->value = ft_strdup(value);
		if (!node->key || !node->value)
			return (free(node->key), free(node->value), free(node), NULL);
		node->alloc = true;
	}
	else
	{
		node->key = key;
		node->value = value;
		node->alloc = false;
	}
	node->next = NULL;
	return (node);
}

int	ft_env_addback(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return (-1);
	if (!*lst)
		return (*lst = new, 0);
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
	new->next = NULL;
	return (0);
}

t_env *ft_env_get(const t_env *lst, const char *key)
{
	while (lst && ft_strcmp(key, lst->key))
		lst = lst->next;
	return (lst);
}

int	*ft_env_set(t_env *lst, const char *key, const char *value, bool alloc)
{
	t_env	*node;

	node = ft_env_get(lst, key);
	if (!node)
		return (ft_env_addback(&lst, ft_env_new(key, value, alloc)));
	if (node->alloc)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			return (-1);
	}
	else
		node->value = value;
	return (1);
}

void	*ft_env_delete(t_env **lst, const char *key)
{
	t_env	*node;
	t_env	*aux;

	if (!lst || !*lst || !key || !*key)
		return ;
	node = ft_env_get(*lst, key);
	if (!node)
		return ;
	aux = *lst;
	while (aux->next != node)
		aux = aux->next;
	aux->next = node->next;
	if (node->alloc)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
	return ;
}
