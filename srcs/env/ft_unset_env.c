/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 05:25:38 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/29 05:31:08 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	ft_unset_env(t_env **env, char *key)
{
	t_env	*node;
	t_env	*aux;

	if (!env || !key || !*env)
		return ;
	node = ft_get_env(*env, key);
	if (!node)
		return ;
	aux = (*env);
	while (aux != node && aux->next != node)
		aux = aux->next;
	aux->next = node->next;
	node->next = NULL;
	free(node->key);
	free(node->value);
	free(node);
}
