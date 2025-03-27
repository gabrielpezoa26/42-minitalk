/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:47:32 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/03/24 21:40:24 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "./libft/libft.h"

typedef struct s_message
{
	unsigned char	c;
	char			*msg;
}	t_message;

#endif

/*
  the goal of this project was to create two simple programs: a server, and a client.
  the client is the easier part, since it is only responsible for sending a message to 
  an server. the server is where a struggled a bit, since it must do a couple thinsgs: print
  the PID, convert the received message (in binary) to actual characters, and assemble the message
  itself. also, the server must print the message as a whole sentence, and not one char at a time. 
*/