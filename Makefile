# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 18:53:10 by gabriel           #+#    #+#              #
#    Updated: 2025/01/19 14:43:41 by gabriel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = server.c client.c
OBJECTS = $(SRC:.c=.o)

CC = cc


all: server client

bonus: server client

server: server.o libft
	$(CC) -o $@ $< -Llibft

client: client.o libft
	$(CC) -o $@ $< -Llibft

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean
	
fclean: clean
	rm -f server client libft/libft.a

re: fclean all