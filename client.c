/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:52:45 by gabriel           #+#    #+#             */
/*   Updated: 2025/01/26 19:04:15 by gabriel          ###   ########.fr       */
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
	size_t	char_index;

	char_index = 0;
	while (char_index < len)  //anda por cada char
	{
		bit_index = 0;
		while (bit_index < 8)  //processa cada char
		{
			if ((message[char_index] >> (7 - bit_index)) & 1)  //move os bits do char atual 1 bit pra direita
				kill(server_pid, SIGUSR1);  //manda '1'
			else
				kill(server_pid, SIGUSR2);  //manda '0'
			bit_index++;
			usleep(1000);  //espera o sinal d volta do server
			while (g_flag == 0)
				pause();
			g_flag = 0;  //reseta pro prox bit
		}
		char_index++;
	}
}

int	main(int argc, char **argv)
{
	unsigned int	server_pid;

	if (argc != 3)  //tratativa d erro
	{
		ft_printf("Format: ./client <server_pid> <message>\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);  //converte pid
	if (server_pid <= 0)  //tratativa d err
	{
		ft_printf("Invalid PID.\n");
		return (1);
	}
	signal(SIGUSR1, ack_signal);  //define func responsavel sinal recebido
	send_message(server_pid, argv[2], ft_strlen(argv[2]) + 1);
	return (0);
}

/*
	ack_signal ->> pega o sinal do servidor avisando q parte da msg chegou
	
	send_message - >> manda a msg char por char, (convertendo), espera o aviso do server; 

	main - >> trata erro de formatação e PID, chama a func de mandar msg
*/