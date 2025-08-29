/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 05:31:57 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/29 05:59:05 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**ft_env_to_arr(t_env *env)
{
	size_t	size;
	size_t	i;
	t_env	*aux;
	char	**result;

	size = 0;
	aux = env;
	while (aux && ++size)
		aux = aux->next;
	result = ft_calloc(sizeof(*result), size + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = ft_append(ft_strdup(env->key), "=", 1);
		result[i] = ft_append(result[i], env->value, ft_strlen(env->value));
		env = env->next;
		i++;
	}
	return (result);
}
