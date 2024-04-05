# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 12:48:48 by eburnet           #+#    #+#              #
#    Updated: 2024/04/05 10:53:32 by eburnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c ft_execute.c
OBJS = $(SRCS:.c=.o)
HEADERS = pipex.h
LIBFT_PATH = ./libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)/libft.a
	cc $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -o $(NAME) -g3

%.o: %.c $(HEADERS)
	cc $(CFLAGS) -c $< -o $@

$(LIBFT_PATH)/libft.a:
	make -C $(LIBFT_PATH)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
