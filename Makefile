# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 18:53:10 by gabriel           #+#    #+#              #
#    Updated: 2025/01/16 17:41:09 by gcesar-n         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

SRC = server.c client.c

CFLAGS = -Wall -Wextra -Werror

INCLUDES	= -I ./libft

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re:
	fclean all
