# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:44:09 by smagniny          #+#    #+#              #
#    Updated: 2023/03/27 16:55:21 by smagniny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CC = gcc 
CFLAGS = -Wall -Werror -Wextra

SRC = main.c \
	inc/Cutils.c inc/ft_split.c inc/str_utils.c 
OBJ = $(SRC:.c=.o)

SRC_BONUS = main_bonus.c \
	inc/Cutils.c inc/ft_split.c inc/str_utils.c 

OBJ_BONUS = $(SRC_BONUS:.c=.o)

R = rm -rf
LIBFT = ./inc/libft
LFLAGS = ./inc/libft.a

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(OBJ_BONUS)
	@if [ -e $(NAME_BONUS) ]; \
	then \
		echo "Nothing to do for bonus"; \
	else \
		$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS); \
	fi

cleanb:
	$(R) $(OBJ_BONUS) $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -Iinc/ -c $< -o $@

clean:
	$(R) $(OBJ)

fclean: clean
	$(R) $(NAME)

re: fclean all