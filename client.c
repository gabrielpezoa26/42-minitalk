/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:52:45 by gabriel           #+#    #+#             */
/*   Updated: 2025/01/19 14:44:26 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "./libft/libft.h"

static void	send_message(char *message)
{
	
}

static int		convert_to_binary(char *to_convert)
{
	
}

int		main(int argc, char **argv)
{
	char	*string_to_print;
	int		*pid;

	if (argc != 3)
	{
		pid = argv[0];
		string_to_print = argv[1];
	}
	return (1);
}

/*
	pid = argv[0];
	string_to_print = argv[1];
*/