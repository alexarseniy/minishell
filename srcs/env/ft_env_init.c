/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 02:45:02 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/29 04:41:52 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	ft_get_env_key_value(char *env, t_kvpair *kv)
{
	char		*sep;

	sep = ft_strchr(env, '=');
	if (sep)
	{
		*sep = '\0';
		kv->key = ft_strdup(env);
		kv->value = ft_strdup(sep + 1);
		if (!kv->key || !kv->value)
			return (1);
		*sep = '=';
	}
	return (0);
}

t_env	*ft_init_env(char **envp)
{
	t_kvpair	kv;
	t_env		*lst;

	lst = NULL;
	while (*envp)
	{
		if (ft_get_env_key_value(*envp, &kv))
			return (free(kv.key), free(kv.value), ft_free_env(lst), NULL);
		if (ft_envlst_addback(&lst, ft_new_env(kv.key, kv.value)))
			return (free(kv.key), free(kv.value), ft_free_env(lst), NULL);
		free(kv.key);
		free(kv.value);
		envp++;
	}
	return (lst);
}
