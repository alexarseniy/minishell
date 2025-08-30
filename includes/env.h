/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 02:03:38 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/30 01:53:02 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>
# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			is_exported;
	struct s_env	*next;
}	t_env;

typedef struct s_kvpair
{
	char	*key;
	char	*value;
}	t_kvpair;

t_env	*ft_init_env(char **envp);
void	ft_free_env(t_env *env);
t_env	*ft_get_env(t_env *env, char *key);
void	ft_set_env(t_env **env, char *key, char *value);
void	ft_unset_env(t_env **env, char *key);
char	**ft_env_to_arr(t_env *env);
int		ft_envlst_addback(t_env **lst, t_env *node);
t_env	*ft_new_env(char *key, char *value);
t_env	*ft_lst_last(t_env *lst);
void	ft_print_env(t_env *lst);

#endif
