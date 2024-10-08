/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:29:18 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/07 14:29:20 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_manager_server(int signal, siginfo_t *info, void *u_context)
{
	static int	i = 8;
	static char	octet;

	(void)u_context;
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
	if (signal == SIGUSR1 || signal == SIGUSR2)
		kill(info->si_pid, SIGUSR1);
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
	action_server.sa_flags = SA_SIGINFO;
	action_server.sa_sigaction = signal_manager_server;
	sigaction(SIGUSR1, &action_server, NULL);
	sigaction(SIGUSR2, &action_server, NULL);
	while (1)
		pause();
	return (0);
}
