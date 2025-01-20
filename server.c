/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:52:52 by gabriel           #+#    #+#             */
/*   Updated: 2025/01/20 12:53:11 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include "libft/libft.h"

static void	signal_handler(int sig)
{
	static int	bit_index;
	static char	current_char;

	if (bit_index == 0 && current_char == 0)
	{
		bit_index = 0;
		current_char = 0;
	}
	if (sig == SIGUSR1)
		current_char |= (1 << (7 - bit_index));
	bit_index++;
	if (bit_index == 8)
	{
		write(1, &current_char, 1);
		if (current_char == '\0')
			write(1, "\n", 1);
		bit_index = 0;
		current_char = 0;
	}
}

int	main(void)
{
	pid_t	pid;
	char	pid_str[12];

	pid = getpid();
	write(1, "Server PID: ", 12);
	pid_str[0] = '\0';
	ft_printf("Server PID: %d\n", pid);
	write(1, pid_str, sizeof(pid_str));
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
