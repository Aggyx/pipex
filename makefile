# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:44:09 by smagniny          #+#    #+#              #
#    Updated: 2023/02/07 19:25:39 by smagniny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc 
CFLAGS = -Wall -Werror -Wextra

SRC = main.c panic.c
OBJ = $(SRC:%.c=%.o)
R = rm -rf
LFLAGS = ./inc/libft.a

all : $(NAME)

$(NAME):  $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

clean:
	$(R) $(OBJ)

fclean:
	clean $(R) $(NAME)

re:
	fclean all