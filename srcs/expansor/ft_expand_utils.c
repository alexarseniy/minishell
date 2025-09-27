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

char *ft_get_env_value(t_sh *shell, char *str, int i)
{
    char    *key;
    char    *value;

    while (str[i] && ft_isalpha(str[i]))
        i++;
    key = ft_substr(str, str + i, ft_strlen(str) - i + 1);
    if (!key)
        return (NULL);
    value =  ft_get_env(shell->env, key);
    free(key);
    return (value);
}

void    ft_realloc_expand(t_sh *shell, char **result, int *i)
{
    char    *start;
    char    *expand;
    char    *end;
    char    *result1;

    if (!result || !i || *i < 0)
        return ;
    start = ft_substr(*result,  0, *i);
    expand = ft_get_env_value(shell, *result, *i);
    while (*result[*i] && ft_isalnum(*result[*i]))
        *i++;
    end = ft_substr(*result, *result + *i, ft_strlen(*result) -  *i + 1);
    if (!start || !end || !expand)
        return (free(start), free(end), free(expand));
    result1 = ft_strjoin(start, expand);
    if (!result1)
        return (free(start), free(end), free(expand));
    free(*result);
    *result = ft_strjoin(result1, end);
    free(start);
    free(expand);
    free(end);
}

char    *ft_expand(t_sh *shell, char *str)
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
            ft_realloc_expand(shell, &result, &(++i));
        i++;
    }
    return (result);
}
