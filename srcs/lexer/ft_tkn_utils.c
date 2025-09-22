/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tkn_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 04:06:35 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/22 04:13:36 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tkn_last(t_token *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_token	*ft_tkn_new(char *value, t_tkn_type type, t_tkn_parts *parts)
{
	t_token	*new;

	if (!value || !type)
		return (NULL);
	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), NULL);
	new->parts = parts;
	new->type = type;
	return (new);
}

void	ft_tkn_addback(t_token **lst, t_token *new)
{
	t_token	*aux;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = ft_tkn_last(*lst);
	aux->next = new;
}
