/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:29:13 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/07 14:29:14 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_wait = 0;

void	send_msg(pid_t serverpid, char c)
{
	int		i;
	char	temp_c;

	i = 7;
	while (i >= 0)
	{
		temp_c = c >> i;
		if ((temp_c >> 0 & 1) == 0)
			kill (serverpid, SIGUSR1);
		else
			kill(serverpid, SIGUSR2);
		while (g_wait == 0)
			;
		g_wait = 0;
		i--;
	}
}

void	signal_manager_client(int signal)
{
	if (signal == SIGUSR1)
		g_wait = 1;
}

int	main(int argc, char *argv[])
{
	int	i;

	signal(SIGUSR1, signal_manager_client);
	if (argc != 3)
	{
		ft_printf("Error\n");
		return (1);
	}
	i = 0;
	while (argv[2][i] != '\0')
	{
		send_msg(ft_atoi(argv[1]), argv[2][i]);
		i++;
	}
	send_msg(ft_atoi(argv[1]), '\0');
	return (0);
}
