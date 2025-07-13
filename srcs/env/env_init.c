/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:39:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/07/13 19:36:39 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "env_core.h"

int	ft_env_init(t_env **env, const char *envp[])
{
	size_t	i;
	char	*new_key;
	char	*new_value;

	i = 0;
	if (!env || !envp)
		return (-1);
	*env = NULL;
	while (envp[i])
	{
		new_key = ft_get_key(envp[i]);
		new_value = ft_get_value(envp[i]);
		if(!new_key || !new_value || ft_add_back(env, new_key, new_value))
			return (free(new_value), free(new_key), ft_env_destroy(*env), -1);
		i++;
		new_key = NULL;
		new_value = NULL;
	}
	return (0);
}
 
void	ft_env_destroy(t_env *e)
{
	t_env *aux;

	if (!e)
		return ;
	while (e)
	{
		aux = e->next;
		free(e->key);
		free(e->value);
		free(e);
		e = aux;
	}
}

const char	*ft_env_get(const t_env *e, const char *key)
{
	if (!e || !key || !*key)
		return (NULL);
	while (e && ft_strcmp(e->key, key))
		e = e->next;
	if (e)
		return (e->value);
	else
		return (NULL);
}

int	ft_env_set(t_env *e, const char *key, const char *value, int overwrite)
{
	t_env	*node;
	char	*dup_key;
	char	*dup_value;

	if (!e || !key || !*key || !value)
		return (-1);
	node = ft_env_get(e, key);
	if (!node)
	{
		dup_key = ft_strdup(key);
		dup_value = ft_strdup(value);
		if (!dup_key || !dup_value || ft_add_back(e, dup_key, dup_value))
			return (free(dup_key), free(dup_value), -1);
	}
	else if (overwrite == 1)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			return (-1);
	}
	else if (ft_add_back(e, dup_key, dup_value, )
		
}
