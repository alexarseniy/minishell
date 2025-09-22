/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:03:34 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 21:07:20 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*ft_env_new(char *key, char *value)
{
	char	*aux_key;
	char	*aux_value;
	t_env	*new;

	if (!key || !value)
		return (NULL);
	new = NULL;
	aux_key = NULL;
	aux_value = NULL;
	new = ft_calloc(sizeof(t_env), 1);
	aux_key = ft_strdup(key);
	aux_value = ft_strdup(value);
	if (!aux_key || !aux_value || !new)
		return (free(new), free(aux_key), free(aux_value), NULL);
	new->next = NULL;
	new->key = aux_key;
	new->value = aux_value;
	return (new);
}
