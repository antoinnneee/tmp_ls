#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abureau <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/14 16:25:25 by abureau           #+#    #+#              #
#    Updated: 2016/11/14 16:25:25 by abureau          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

SRC = ./src/main.c \
	./src/l_mod.c \
	./src/sort.c \
	./src/parser.c \
	./src/is_sort.c \
	./src/secure_cat.c \
	./src/sizu.c \
	./src/lltoa_base.c \
	./src/size.c \
	./src/read.c \
	./src/creat_elem_b.c \
	./src/more_sort.c \
	./src/create_elem.c \
	./src/print.c \
	./src/print_addon.c

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
