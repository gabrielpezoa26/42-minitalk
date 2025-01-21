/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:52:52 by gabriel           #+#    #+#             */
/*   Updated: 2025/01/20 21:52:16 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include "./libft/libft.h"

static void	signal_handler(int sig)
{
	static int	bit_count;
	static char	current_char;

	if (bit_count == 0 && current_char == 0)
	{
		bit_count = 0;
		current_char = 0;
	}
	if (sig == SIGUSR1)
		current_char |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		// if (current_char == '\0')
		// 	ft_printf("\n");
		// else
		ft_printf("%c", current_char);
		bit_count = 0;
		current_char = 0;
	}
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
