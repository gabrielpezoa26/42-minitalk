# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 18:53:10 by gabriel           #+#    #+#              #
#    Updated: 2025/01/27 15:53:10 by gcesar-n         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = server.c client.c
OBJECTS = server.o client.o

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: server client

server: server.o libft/libft.a
	$(CC) $(CFLAGS) -o server server.o -Llibft -lft

client: client.o libft/libft.a
	$(CC) $(CFLAGS) -o client client.o -Llibft -lft

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c -o client.o

libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean

fclean: clean
	rm -f server client
	make -C libft fclean

re: fclean all
