/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:20:14 by olarseni          #+#    #+#             */
/*   Updated: 2025/07/13 18:36:46 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// TYPEDEF
typedef struct s_env	t_env;

// Create and destroy
int			ft_env_init(t_env **env, const char *envp[]);
void		ft_env_destroy(t_env *env);

// Getters and setters
const char	*ft_env_get(const t_env *e, const char *key);
int			ft_env_set(t_env *e, const char *key, const char *value, int overwrite);
int			ft_env_unset(t_env *e, const char *key);

// List -> array of strings
char		**ft_env_export(const t_env *e);
void		ft_env_array_free(char **arr);

#endif
