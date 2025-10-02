/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delquote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:43:20 by olarseni          #+#    #+#             */
/*   Updated: 2025/10/02 04:01:30 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_delquotes_loop_actions(char **str, char **result, int i, int *j)
{
	static int	in_quote = 0;
	static char	quote = 0;

	if (!in_quote && ((*str)[i] == '\'' || (*str)[i] == '"'))
	{
		in_quote = 1;
		quote = (*str)[i];
	}
	else if (in_quote && ((*str)[i] == '\'' || (*str)[i] == '"')
		&& (*str)[i] == quote)
		in_quote = 0;
	else
	{
		*result = ft_realloc(*result, *j + 1, *j + 2);
		if (!*result)
			return ;
		(*result)[*j] = (*str)[i];
		(*j) += 1;
	}
}

char	*ft_delquotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = NULL;
	while (str[i])
	{
		ft_delquotes_loop_actions(&str, &result, i, &j);
		i++;
	}
	if (!result)
		return (ft_strdup(""));
	return (result);
}

void	*ft_realloc(void *ptr, size_t actual_size, size_t new_size)
{
	void	*result;

	if (!ptr)
		return (ft_calloc(new_size, 1));
	if (ptr && (new_size == 0))
		return (ft_bzero(ptr, actual_size), free(ptr), NULL);
	result = ft_calloc(new_size, 1);
	if (new_size < actual_size)
		ft_memmove(result, ptr, new_size);
	else
		ft_memmove(result, ptr, actual_size);
	return (free(ptr), result);
}
