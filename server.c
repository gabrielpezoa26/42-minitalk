/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:52:52 by gabriel           #+#    #+#             */
/*   Updated: 2025/01/21 15:18:20 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//static t_message	g_to_print = {0, 0};

static void	handle_signal_update(int sig, int *bit_count, char *current_char)
{
	if (sig == SIGUSR1)
		*current_char |= (1 << (7 - *bit_count));
	(*bit_count)++;
	if (*bit_count == 8)
	{
		if (*current_char == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", *current_char);
		*bit_count = 0;
		*current_char = 0;
	}
}

static void	signal_handler(int sig)
{
	static int	bit_count = 0;
	static char	current_char = 0;

	handle_signal_update(sig, &bit_count, &current_char);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
