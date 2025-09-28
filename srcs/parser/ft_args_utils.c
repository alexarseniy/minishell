/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:49:31 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/28 23:50:42 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*ft_args_last(t_args *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_args_addback(t_args **lst, t_args *new)
{
	t_args	*aux;

	if (!lst)
		return ;
	aux = *lst;
	if (!aux)
	{
		*lst = new;
		return ;
	}
	aux = ft_args_last(aux);
	aux->next = new;
}
