/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:30:29 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 22:52:03 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_get_env(t_env *env, char *key)
{
	int	key_len;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	while (env && (ft_strncmp(env->key, key, key_len)
			|| key_len != (int)ft_strlen(env->key)))
		env = env->next;
	if (!env)
		return (NULL);
	return (env->value);
}
