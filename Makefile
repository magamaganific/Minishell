# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/14 17:43:41 by elengarc          #+#    #+#              #
#    Updated: 2025/06/14 17:43:42 by elengarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCS = minishell.c aux.c parse_prompt.c tokenizer.c errors.c free_mem_funcs.c parsing_utils.c handle_inputs.c handle_outputs.c execs.c execs2.c execs3.c execs4.c tokenizer2.c tokenizer3.c expand_variables.c expand_variables2.c built_in.c built_in2.c built_in3.c signals.c

OBJS = $(SRCS:.c=.o)

# Ruta a tu libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -lreadline -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

