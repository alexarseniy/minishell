/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_addback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:07:42 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 22:51:32 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	ft_env_addback(t_env **lst, t_env *new)
{
	t_env	*aux;

	if (!lst)
		return (-1);
	aux = *lst;
	if (!aux)
	{
		*lst = new;
		return (0);
	}
	aux = ft_last_env(aux);
	aux->next = new;
	return (0);
}
