/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:35:19 by olarseni          #+#    #+#             */
/*   Updated: 2025/07/12 17:20:03 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// OOTB INCLUDES

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// CUSTOM INCLUDES
# include "env.h"

// TYPEDEFS

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_next	*next;
}	t_env;

typedef struct s_shell
{
	struct s_env	*env;
	char			*usr_input;
	int				status;
}	t_shell;

// Functions

int	init_shell(t_shell *sh, char *envp[]);
int	start_shell(t_shell *sh);
int	free_shell(t_shell *sh);

#endif
