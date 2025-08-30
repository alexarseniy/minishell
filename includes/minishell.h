/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:06:47 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/30 15:23:54 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

// CUSTOM INCLUDES
# include "libft.h"
# include "env.h"
# include "signals.h"
# include "parser.h"

// defines
# define PROMPT "\33[38;5;65mminishell:\33[0m "

#endif
