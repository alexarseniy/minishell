/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getset_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 05:01:04 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/29 06:19:11 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdbool.h>

t_env	*ft_get_env(t_env *env, char *key)
{
	if (!env || !key)
		return (NULL);
	while (env && ft_strncmp(key, env->key, ft_strlen(key)))
		env = env->next;
	return (env);
}

void	ft_set_env(t_env **env, char *key, char *value)
{
	t_env	*node;
	char	*new_value;

	node = ft_get_env(*env, key);
	if (!node && ft_envlst_addback(env, ft_new_env(key, value)))
		return ;
	else
	{
		if (!value)
			new_value = ft_strdup("");
		else
			new_value = ft_strdup(value);
		if (!new_value)
			return ;
		free(node->value);
		node->value = new_value;
		node->is_exported = true;
	}
}
