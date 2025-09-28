/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:27:39 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/28 23:33:37 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_expand_ptr(char *str)
{
	int	i;
	int	is_squote;

	i = 0;
	is_squote = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (!is_squote && str[i] == '\'')
			is_squote = 1;
		else if (is_squote && str[i] == '\'')
			is_squote = 0;
		else if (!is_squote && str[i] == '$' && ft_isalpha(str[i + 1]))
			return (str + i);
		else if (!is_squote && str[i] == '$' && str[i + 1] == '?')
			return (str + i);
		else if (!is_squote && str[i] == '$' && str[i + 1] == '_')
			return (str + i);
		i++;
	}
	return (NULL);
}

int	ft_has_expand(char *str)
{
	int	i;
	int	is_squote;

	i = 0;
	is_squote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!is_squote && str[i] == '\'')
			is_squote = 1;
		else if (is_squote && str[i] == '\'')
			is_squote = 0;
		else if (!is_squote && str[i] == '$' && ft_isalpha(str[i + 1]))
			return (1);
		else if (!is_squote && str[i] == '$' && str[i + 1] == '?')
			return (1);
		else if (!is_squote && str[i] == '$' && str[i + 1] == '_')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_expand_ptr(t_sh *shell, char *ptr)
{
	char	*key;
	char	*result;
	int		end;

	if (!ptr)
		return (shell->err = ERR_EXPAND, NULL);
	end = 0;
	while (ptr[end] && (ft_isalnum(ptr[end])
			|| ptr[end] == '?' || ptr[end] == '_'))
		end++;
	key = ft_substr(ptr, 0, end);
	if (!key)
		return (shell->err = ERR_EXPAND, NULL);
	result = ft_get_env(shell->env, key);
	if (result)
		result = ft_strdup(result);
	return (result);
}

char	*ft_expand(t_sh *shell, char *str)
{
	char	*expand_ptr;
	char	*expanded_ptr;
	char	*start_to_ptr;
	char	*aux;
	char	*aux2;

	expand_ptr = ft_get_expand_ptr(str);
	if (!expand_ptr)
		return (shell->err = ERR_EXPAND, NULL);
	expanded_ptr = ft_expand_ptr(shell, ++expand_ptr);
	if (!expanded_ptr)
		expanded_ptr = ft_strdup("");
	start_to_ptr = ft_substr(str, 0, expand_ptr - str - 1);
	if (!start_to_ptr)
		return (free(expanded_ptr), NULL);
	aux = ft_strjoin(start_to_ptr, expanded_ptr);
	free(expanded_ptr);
	free(start_to_ptr);
	if (!aux)
		return (NULL);
	while (*expand_ptr && (ft_isalnum(*expand_ptr)
			|| *expand_ptr == '_' || *expand_ptr == '?'))
		expand_ptr++;
	aux2 = ft_strjoin(aux, expand_ptr);
	return (free(aux), aux2);
}
