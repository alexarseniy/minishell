/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:43:24 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/28 23:44:00 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_last(t_cmd *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_cmd_addback(t_cmd **lst, t_cmd *new)
{
	t_cmd	*aux;

	if (!lst)
		return ;
	aux = *lst;
	if (!aux)
	{
		*lst = new;
		return ;
	}
	aux = ft_cmd_last(aux);
	aux->next = new;
	return ;
}
