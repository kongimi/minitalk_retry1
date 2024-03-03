/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:55:19 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/03 11:06:17 by npiyapan         ###   ########.fr       */
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
	static int				i = 0;
	static unsigned char	c = 0;

	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		ft_printf("Receive : %c\n", c);
		exit (0);
		c = 0;
	}
	else
		c <<= 1;
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
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(300);
		}
	}
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

// int	main(int argc, char **argv)
// {
// 	char				*line;
//
// 	if (argc != 3 || !ft_strlen(argv[2]))
// 		return (1);
// 	ft_printf("Client PID : %d\n", getpid());
// 	signal(SIGUSR1, action);
// 	signal(SIGUSR2, action);
// 	send_to_server(ft_atoi(argv[1]), argv[2]);
// 	while (1)
// 	{
// 		line = get_next_line(0);
// 		if (line[0] == '\n')
// 			break ;
// 		send_to_server(ft_atoi(argv[1]), line);
// 		free (line);
// 	}
// 	return (0);
// }
