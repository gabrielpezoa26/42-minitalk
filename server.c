/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:52:52 by gabriel           #+#    #+#             */
/*   Updated: 2025/01/26 18:09:57 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_to_print = {0, 0};

static void	ft_assemble_msg(void)
{
	char	*temp;
	char	c;

	temp = NULL;
	c = (char)g_to_print.c;
	if (g_to_print.msg != NULL)  //se ja tiver algo, concatena e libera a memória
	{
		temp = ft_strjoin(g_to_print.msg, &c);  //concatena a msg a partir de '&c'
		free(g_to_print.msg);
	}
	else
		temp = ft_strdup(&c);  //cria nova string, so oq tem em "c"
	if (temp == NULL)
		exit(EXIT_FAILURE);
	g_to_print.msg = temp; //aponta pra nova string
}

static void	ft_print_character(void)
{
	if (g_to_print.c == '\0')  //é pq chegou no final da string
	{
		if (g_to_print.msg != NULL)
			ft_printf("%s\n", g_to_print.msg);  //printa os bagui, %s
		else
			ft_printf("\n"); 
		free(g_to_print.msg);
		g_to_print.msg = NULL;  //reseta o ponteiro
	}
	else
		ft_assemble_msg();  //se n tiver "completa"
	g_to_print.c = 0;  //reseta e prepara pro prox char
}

static void	ft_handle_signal(int signal, siginfo_t *info, void *context)
{
	static int	bit_count = 0;

	(void)context;  //prototipo
	if (signal == SIGUSR1) 
		g_to_print.c = (g_to_print.c << 1) | 1;  //muda os bit uma posic pra esquerda, dando espaço pro prox
	else if (signal == SIGUSR2)
		g_to_print.c = (g_to_print.c << 1);  // n precisa do "| 1" pq já é zero
	bit_count++;
	if (bit_count == 8)  //qdo acumula 8 bits é pq formou um char
	{
		ft_print_character();
		bit_count = 0;  //reseta
	}
	if (kill(info->si_pid, SIGUSR1) == -1)  //"avisa" que recebeu o bit
		exit(EXIT_FAILURE);  //se a func "kill" der ruim
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());  //printa o PID
	sa.sa_sigaction = ft_handle_signal;  //fala qual func trata dos sinais
	sa.sa_flags = SA_SIGINFO;  // permite o uso do struct "siginfo" pela func de signal_handle
	sigemptyset(&sa.sa_mask);  //define q n vai bloquear nenhum sinal
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}

/*
	build_msg - >> monta a msg char por char, cuida da memoria ()

	print_char ->> printa qdo a msg foi inteiramente recebida

	handle_signal - >> 

	main ->> pega e imprime o PID;  chama as funçoes
*/