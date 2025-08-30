/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:27:40 by olarseni          #+#    #+#             */
/*   Updated: 2025/08/30 16:02:28 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_tkn_type
{
	WORD;
	PIPE;
	REDIR_IN;
	REDIR_OUT;
	REDIR_APPEND;
	HEREDOC;
} t_tkn_type;

typedef struct s_token
{
	char		*token;
	t_tkn_type	type;
} t_token;

#endif
