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
	static int	i;
	static char	octet;

	if (signal == SIGUSR1)
		octet = octet | 0;
	else if (signal == SIGUSR2)
		octet = octet | 1;
	i++;
	if (i == 8)
	{
		if (octet == 0)
			ft_printf("\n");
		else
			ft_printf("%c", octet);
		i = 0;
		octet = 0;
	}
	else
		octet = octet << 1;
}

int	main(void)
{
	struct sigaction	action_server;
	pid_t				serverpid;

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
