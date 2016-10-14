#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abureau <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/13 16:10:27 by abureau           #+#    #+#              #
#    Updated: 2016/10/13 16:10:27 by abureau          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ls

SRC = ./src/creat_elem_b.c \
	./src/print_addon.c \
	./src/secure_cat.c \
	./src/l_mod.c \
	./src/lltoa_base.c \
	./src/create_elem.c \
	./src/is_sort.c \
	./src/main.c \
	./src/more_sort.c \
	./src/read.c \
	./src/parser.c \
	./src/sort.c \
	./src/print.c

CC = gcc

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

all: LIBCOMPILE $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ -I libft/includes -L libft/ -lft

LIBCOMPILE:
	 make -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -I libft/includes -o $@ -c $<

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
