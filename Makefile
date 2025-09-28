# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/13 16:40:07 by olarseni          #+#    #+#              #
#    Updated: 2025/09/28 23:56:59 by olarseni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================= #
# 									Variables
# ============================================================================= #

# Program name
NAME	=	minishell

# Sources
VPATH	=	srcs srcs/env srcs/error srcs/utils srcs/expansor srcs/lexer srcs/parser \
			srcs/quote_del srcs/signal srcs/executor srcs/heredoc
SRCS	=	main.c					\
			ft_arr_to_env.c			\
			ft_env_addback.c		\
			ft_env_basic_utils.c	\
			ft_env_new.c			\
			ft_env_to_arr.c			\
			ft_get_env.c			\
			ft_set_env.c			\
			errors.c				\
			ft_err_wrap_01.c		\
			ft_err_wrap_02.c		\
			ft_clean.c				\
			ft_clean_utils.c		\
			minishell_setup_utils.c	\
			ft_lexer.c				\
			ft_parser.c				\
			ft_parser_utils.c		\
			ft_args_utils.c			\
			ft_cmd_add_components.c	\
			ft_cmd_utils.c			\
			ft_print_cmd.c			\
			ft_redir_utils.c		\
			ft_execute.c			\
			ft_heredoc.c			\
			ft_delquote.c			\
			ft_handlers.c			\
			ft_lexer_utils_01.c		\
			ft_tkn_utils.c			\
			ft_expansor.c			\
			ft_expansor_cmd_name.c	\
			ft_expansor_utils.c

# Objects
ODIR	=	objects
OBJS	=	$(SRCS:%.c=$(ODIR)/%.o)

# includes
IDIR	=	includes

# LIBFT
LDIR	=	libft
LIBFT	=	libft.a
LPRINTF	=	libft/ft_printf/includes

# Compiler
CC	=	cc

# FLAGS
CFLAGS	=	-Wall -Werror -Wextra
IFLAGS	=	-I$(IDIR) -I$(LDIR) -I$(LPRINTF)
LFLAGS	=	-L$(LDIR) -lft -lreadline
SANITIZE=	-fsanitize=address
LIBSAN	=	-static-libsan
DEBUG	=	-g

# ============================================================================= #
# 									RULES										#
# ============================================================================= #

all: $(NAME)

$(ODIR)/%.o: %.c | $(ODIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<  $(DEBUG) $(SANITIZE)

$(NAME): $(OBJS)
	@make --silent -C $(LDIR) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^ $(LFLAGS) $(DEBUG) $(SANITIZE) $(LIBSAN)

debug: $(DOBJS)
	@make --silent -C $(LDIR) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $^ $(LFLAGS) 

$(LIBFT):
	@make --silent -C $(LDIR)

$(ODIR):
	@mkdir -p $(ODIR)

clean:
	@rm -rf $(ODIR)
	@$(MAKE) --silent -C $(LDIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --silent -C $(LDIR) fclean

re: fclean all

.PHONY: all clean fclean re 
