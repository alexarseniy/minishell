/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:48:00 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 02:49:47 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_new_redir(char *value, t_redir_type type)
{
	t_redir	*new;

	if (!value || !type)
		return (NULL);
	new = ft_calloc(sizeof(t_redir), 1);
	if (!new)
		return (NULL);
	new->file = ft_strdup(value);
	if (!new->file)
		return (free(new), NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}

t_redir	*ft_redir_last(t_redir *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_redir_addback(t_redir **lst, t_redir *new)
{
	t_redir	*aux;

	if (!lst)
		return ;
	aux = *lst;
	if (!aux)
	{
		*lst = new;
		return ;
	}
	aux = ft_redir_last(aux);
	aux->next = new;
}
