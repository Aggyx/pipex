# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:44:09 by smagniny          #+#    #+#              #
#    Updated: 2023/02/18 17:28:06 by smagniny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc 
CFLAGS = -Wall -Werror -Wextra

SRC = main.c Cutils.c
OBJ = $(SRC:%.c=%.o)
R = rm -rf
LFLAGS = ./inc/libft.a

all : $(NAME)

$(NAME):  $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

clean:
	$(R) $(OBJ)

fclean: clean
	$(R) $(NAME)

re: fclean all