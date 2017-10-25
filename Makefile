# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/27 16:44:56 by mvelluet          #+#    #+#              #
#    Updated: 2017/10/17 22:24:20 by mvelluet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC = 	main.c \
		hooks.c \
		hooks2.c \
		draw.c \
		draw_wolf.c \
		load_map.c \
		load_blocks.c \
		move.c \
		basics.c \
		basics_2.c

CFLAGS = -Wall -Wextra -Werror

INCLUDE = wolf.h

OBJ = $(SRC:.c=.o)

CC = gcc

.PHONY: clean fclean all re libft

all: $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -I libft -c $<

libft:
	make -C libft

$(NAME): $(OBJ) libft
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) -L libft -lft -lmlx -lm -framework OpenGL -framework AppKit libft/libft.a
	@echo "wolf3d done" 

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
	