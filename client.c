/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:55:19 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/03 11:06:33 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"
#include "libft/include/get_next_line.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

static void	action(int sig)
{
	if (sig == SIGUSR2)
		ft_printf("Received sig from Server.\n");
}

static void	send_to_server(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					exit (1);
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					exit (1);
			}
			usleep(300);
		}
	}
	exit (0);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3 || !ft_strlen(argv[2]))
		handle_errors("Usage : ./clinet ServerPID Message.");
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
			handle_errors("Server PID not digit.");
		i++;
	}
	ft_printf("Client PID : %d\n", getpid());
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	send_to_server(ft_atoi(argv[1]), argv[2]);
	while (1)
		usleep(300);
	return (0);
}
