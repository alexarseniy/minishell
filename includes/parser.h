/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:27:40 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/02 17:30:40 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_tkn_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	ASSIGNMENT
} t_tkn_type;

typedef enum e_quote_type
{
	NONE,
	DB_QUOTE,
	SG_QUOTE
} t_quote_type;

typedef struct t_tkn_part
{
	char			*value;
	t_quote_type	quote_type;
	t_tkn_part		*next;
}

typedef struct s_token
{
	char	*operation;
	t_part	*tkn_parts;
	t_tkn_type	type;
} t_token;


#endif
