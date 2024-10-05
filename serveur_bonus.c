#include "minitalk.h"

void	signal_manager_server(int signal, siginfo_t *info, void *u_context)
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
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
			usleep(420);
		}
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
	action_server.sa_flags = SA_SIGINFO;
	action_server.sa_sigaction = signal_manager_server;
	sigaction(SIGUSR1, &action_server, NULL);
	sigaction(SIGUSR2, &action_server, NULL);
	while (1)
		pause();
	return (0);
}
