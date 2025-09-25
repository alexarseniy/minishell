/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_to_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:05:27 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/25 17:22:14 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static char	*ft_get_env_key(char *env)
{
	char	*result;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (NULL);
	result = ft_substr(env, 0, i);
	return (result);
}

static char	*ft_get_env_value(char *env)
{
	char	*result;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	env = ft_strchr(env, '=');
	if (!env)
		return (NULL);
	env++;
	if (!env[i])
		result = ft_strdup("");
	else
		result = ft_substr(env, 0, ft_strlen(env) + 1);
	return (result);
}

t_env	*ft_arr_to_env(char *envp[])
{
	t_env	*result;
	t_env	*new;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	result = NULL;
	new = NULL;
	while (envp[i])
	{
		key = ft_get_env_key(envp[i]);
		if (!key)
			return (NULL);
		value = ft_get_env_value(envp[i++]);
		if (!value)
			return (free(key), NULL);
		new = ft_env_new(key, value);
		if (!new || ft_env_addback(&result, new))
			return (free(key), free(value), free(new), NULL);
		free(key);
		free(value);
	}
	return (result);
}
