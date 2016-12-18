# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 21:06:34 by kacoulib          #+#    #+#              #
#    Updated: 2016/12/13 23:36:58 by kacoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  fillit
HEADERS	= fillit.h
SOURCES = fillit.c
OBJ	= $(SOURCES:.c=.o)
FLAGS	= -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
		gcc $(FLAGS) -c $(HEADERS) $(SOURCES)  
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)
clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
re : fclean all
