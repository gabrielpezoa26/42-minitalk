/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:52:52 by gabriel           #+#    #+#             */
/*   Updated: 2025/01/26 12:40:48 by gcesar-n         ###   ########.fr       */
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
	if (g_to_print.msg)
	{
		temp = ft_strjoin(g_to_print.msg, &c);
		free(g_to_print.msg);
	}
	else
		temp = ft_strdup(&c);
	if (!temp)
		exit(EXIT_FAILURE);
	g_to_print.msg = temp;
}

static void	ft_print_character(void)
{
	if (g_to_print.c == '\0')
	{
		if (g_to_print.msg)
			ft_printf("%s\n", g_to_print.msg);
		else
			ft_printf("\n");
		free(g_to_print.msg);
		g_to_print.msg = NULL;
	}
	else
		ft_assemble_msg();
	g_to_print.c = 0;
}

static void	ft_handle_signal(int signal, siginfo_t *info, void *context)
{
	static int	bit_count = 0;

	(void)context;
	if (signal == SIGUSR1)
		g_to_print.c = (g_to_print.c << 1) | 1;
	else if (signal == SIGUSR2)
		g_to_print.c = (g_to_print.c << 1);
	bit_count++;
	if (bit_count == 8)
	{
		ft_print_character();
		bit_count = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = ft_handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
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