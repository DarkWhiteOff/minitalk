/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:23:31 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/06 19:23:33 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_manager_server(int signal)
{
	static int	i = 8;
	static char	octet;

	if (signal == SIGUSR1)
		octet = octet | 0;
	else if (signal == SIGUSR2)
		octet = octet | 1;
	i--;
	if (i > 0)
		octet = octet << 1;
	else if (i == 0)
	{
		if (octet == 0)
			ft_printf("\n");
		else
			ft_printf("%c", octet);
		i = 8;
		octet = 0;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	action_server;
	pid_t				serverpid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error\n");
		return (1);
	}
	serverpid = getpid();
	ft_printf("Server ID : %d\n", serverpid);
	sigemptyset(&action_server.sa_mask);
	action_server.sa_flags = 0;
	action_server.sa_handler = signal_manager_server;
	sigaction(SIGUSR1, &action_server, NULL);
	sigaction(SIGUSR2, &action_server, NULL);
	while (1)
		pause();
	return (0);
}
