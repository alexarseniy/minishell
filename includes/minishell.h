/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:33:30 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/22 07:45:30 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* OOTB HEADERS */
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

/* CUSTOM HEADERS */
# include "libft.h"
# include "env.h"

/* Define colors */
# define CRED	"\033[38;5;124m"
# define CGREEN	"\033[38;5;101m"
# define RESET	"\033[0m"

/* Typedef enum */
typedef enum e_error
{
	NONE = 0,
	ERROR,
	ERR_SETUP_SHELL,
	ERR_INPUT,
	ERR_NO_INPUT,
	ERR_STRDUP_ERR,
	ERR_LEXER,
	ERR_ENV,
	ERR_PARSER,
	ERR_EXPAND,
	ERR_DELQUOTE,
	ERR_HEREDOC,
	ERR_EXECUTE,
	ERR_FORBIDDEN_CHAR,
	ERR_UNCLOSED_QUOTES,
	ERR_HANDLE_OP_SUBSTR,
	ERR_HANDLE_OP_TKN_NEW,
	ERR_INVALID_OP_WORD,
	ERR_HANDLE_WORD_SUBSTR,
	ERR_HANDLE_WORD_TKN_NEW,
	ERR_SYNTAX,
	ERR_MEMMORY
}	t_error;

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE
}	t_redir_type;

typedef enum e_tkn_type
{
	TKN_NONE,
	TKN_REDIR_IN,
	TKN_REDIR_OUT,
	TKN_REDIR_APPEND,
	TKN_REDIR_HERE,
	TKN_PIPE,
	TKN_WORD,
	TKN_ASSIGN
}	t_tkn_type;

typedef enum e_part_type
{
	NO_QUOTE,
	S_QUOTE,
	D_QUOTE
}	t_part_type;

/* Typedefs */
typedef struct s_sh			t_sh;
typedef struct s_cmd		t_cmd;
typedef struct s_token		t_token;
typedef struct s_tkn_parts	t_tkn_parts;
typedef struct s_redir		t_redir;
typedef struct s_here		t_here;
typedef struct s_args		t_args;
typedef t_error				(*t_err_wrap)(t_sh *);

/* Typedef Structs */
typedef struct s_args
{
	char	*value;
	t_args	*next;
}	t_args;

typedef struct s_tkn_parts
{
	char		*value;
	t_part_type	type;
	t_tkn_parts	*next;
}	t_tkn_parts;

typedef struct s_here
{
	char	*content;
	char	*del;
	int		expand;
	int		pipe_fd[2];
	t_here	*next;
}	t_here;

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	t_redir			*next;
}	t_redir;

typedef struct s_token
{
	char		*value;
	t_tkn_type	type;
	t_tkn_parts	*parts;
	t_token		*next;
}	t_token;

typedef struct s_cmd
{
	char	*cmd_name;
	t_args	*args;
	t_env	*env_tmp;
	t_redir	*redirs;
	t_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	t_token				*tkn;
	t_here				*here;
	t_error				err;
	t_env				*env;
	t_cmd				*cmd_lst;
	char				*input;
	int					last_exit_status;
	int					interactive_mode;
	const t_err_wrap	*err_wrap;
}	t_sh;

/* Setup Utils */
int					ft_setup_shell(t_sh *shell, int argc, char **argv,
						char *envp[]);
int					ft_set_interactive_cmd_mode(t_sh *shell, int argc,
						char **argv);
int					ft_create_envp(t_sh *shell, char *envp[]);
const t_err_wrap	*ft_get_wrappers(void);
void				ft_clean(t_sh *sh);
void				ft_clean_all(t_sh *sh);
void				ft_clean_here(t_sh *sh);
void				ft_clean_cmd(t_sh *sh);
void				ft_clean_tkns(t_sh *sh);
void				ft_get_input(t_sh *shell);
//void				ft_free_parts(t_token *tkn);
void				ft_free_redirs(t_redir *redirs);
/* Main function flow */
void				ft_execute(t_sh *shell);
void				ft_expand(t_sh *shell);
void				ft_heredoc(t_sh *shell);
void				ft_lexer(t_sh *shell);
void				ft_parser(t_sh *shell);
void				ft_delquote(t_sh *shell);
/* LEXER */
/* Lexer handlers */
void				ft_handle_operator(t_token **tkn, char *input, int *i,
						t_sh *sh);
void				ft_handle_word(t_token **tkn, char *input, int *i,
						t_sh *sh);
/* Lexer utils */
int					ft_is_operator(char c);
int					ft_is_valid_op(char *input, int i);
void				ft_print_tkn(t_token *tkn);
t_tkn_type			ft_get_tkn_type(char *str);
/* Tokens utils */
void				ft_tkn_addback(t_token **lst, t_token *new);
t_token				*ft_tkn_new(char *value, t_tkn_type type,
						t_tkn_parts *parts);
t_token				*ft_tkn_last(t_token *lst);
/* ERROR WRAPPERS */
t_error				wrap_lexer(t_sh *shell);
t_error				wrap_parser(t_sh *shell);
t_error				wrap_expand(t_sh *shell);
t_error				wrap_delquote(t_sh *shell);
t_error				wrap_heredoc(t_sh *shell);
t_error				wrap_execute(t_sh *shell);
/* Exit error */
t_error				ft_exit_err(t_sh *shell);
void				ft_print_err(t_sh *shell);

#endif
