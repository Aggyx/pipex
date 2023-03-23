# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:44:09 by smagniny          #+#    #+#              #
#    Updated: 2023/03/23 12:43:55 by smagniny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
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
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)

cleanb:
	$(R) $(OBJ_BONUS) $(NAME)

clean:
	$(R) $(OBJ)

fclean: clean
	$(R) $(NAME)

re: fclean all