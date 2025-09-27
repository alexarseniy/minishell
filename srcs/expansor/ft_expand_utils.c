/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:05:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 23:05:46 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_has_expand(char *str)
{
    if (!str)
        return (0);
    if (str[0] == '\'')
        return (0);
    if (!ft_strchr(str, '$'))
        return (0);
    return (1);
}

void    ft_next_expand(char *str, int *i)
{
    int start;
    int end;

    start = *i;

    end = start;
}

void    ft_realloc_expand(char **result, int *i)
{
    char *aux;

    if (!result || i < 0)
        return ;
    aux = *result;
}

char    *ft_expand(char *str)
{
    char    *result;
    int     s_quote;
    int     i;

    result = ft_strdup(str);
    i = 0;
    s_quote = 0;
    while (result && result[i])
    {
        if (result[i] == '\'')
            s_quote = 1;
        if (s_quote == 1 && result[i] == '\'')
            s_quote = 0;
        if (s_quote == 0 && result[i] == '$' && (ft_isalpha(result[i + 1]) || result[i + 1] == '?'))
            ft_realloc_expand(&result, &i);
        i++;
    }
    return (result);
}