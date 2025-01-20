# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 18:53:10 by gabriel           #+#    #+#              #
#    Updated: 2025/01/20 12:25:15 by gabriel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = server.c client.c
OBJECTS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: server client

server: server.o libft/libft.a
	$(CC) $(CFLAGS) -o server server.o -Llibft -lft

client: client.o libft/libft.a
	$(CC) $(CFLAGS) -o client client.o -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean

fclean: clean
	rm -f server client
	make -C libft fclean

re: fclean all
