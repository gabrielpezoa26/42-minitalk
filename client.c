/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:52:45 by gabriel           #+#    #+#             */
/*   Updated: 2025/01/26 13:57:29 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_flag = 0;

static void	ack_signal(int signal)
{
	if (signal == SIGUSR1)
		g_flag = 1;
}

static void	send_message(unsigned int server_pid, char *message, size_t len)
{
	int		bit_index;
	size_t	i;

	i = 0;
	while (i < len)
	{
		bit_index = 0;
		while (bit_index < 8)
		{
			if ((message[i] >> (7 - bit_index)) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			bit_index++;
			usleep(1000);
			while (!g_flag)
				pause();
			g_flag = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	unsigned int	server_pid;

	if (argc != 3)
	{
		ft_printf("Format: ./client <server_pid> <message>\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Invalid PID.\n");
		return (1);
	}
	signal(SIGUSR1, ack_signal);
	send_message(server_pid, argv[2], ft_strlen(argv[2]) + 1);
	return (0);
}

/*
	ack_signal ->> pega o sinal do servidor avisando q parte da msg chegou
	
	send_message - >> manda a msg char por char, (convertendo), espera o aviso do server; 

	main - >> trata erro de formatação e PID, chama a func de mandar msg
*/