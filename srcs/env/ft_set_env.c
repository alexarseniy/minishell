/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:50:47 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/25 18:40:37 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	ft_set_env(t_env **env, char *key, char *value)
{
	t_env	*new;

	if (!env || !key)
		return (-1);
	if (!value)
		new = ft_env_new(key, "");
	else
		new = ft_env_new(key, value);
	if (!new)
		return (-1);
	ft_env_addback(env, new);
	return (0);
}
