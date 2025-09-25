/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:20:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/25 18:41:19 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/* INCLUDE CUSTOM HEADERS */
# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*ft_env_new(char *key, char *value);
int		ft_env_addback(t_env **lst, t_env *new);
int		ft_get_env_len(t_env *env);
t_env	*ft_last_env(t_env *env);
t_env	*ft_arr_to_env(char *envp[]);
char	**ft_env_to_arr(t_env *env);
char	*ft_get_env(t_env *env, char *key);
int		ft_set_env(t_env **env, char *key, char *value);

#endif
