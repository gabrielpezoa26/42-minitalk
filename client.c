/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:52:45 by gabriel           #+#    #+#             */
/*   Updated: 2025/01/20 12:42:25 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include "./libft/libft.h"

static void	send_message(pid_t server_pid, char *message)
{
	char	current_char;
	int		bit_index;

	while (*message)
	{
		current_char = *message;
		bit_index = 7;
		while (bit_index >= 0)
		{
			if ((current_char >> bit_index) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(100);
			bit_index--;
		}
		message++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;

	if (argc != 3)
	{
		write(1, "Usage: ./client <server_pid> <message>\n", 39);
		return (1);
	}
	server_pid = (pid_t)ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		write(1, "Invalid PID.\n", 13);
		return (1);
	}
	message = argv[2];
	send_message(server_pid, message);
	return (0);
}
