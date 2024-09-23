#include "minitalk.h"

void	ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)str;
	while (i < n)
	{
		s[i] = '\0';
		i++;
	}
}

void    decrypt_msg(int signal)
{
    static int i;
    static unsigned char    strbit[256];

    if (signal == SIGUSR1)
        strbit[i] = '0';
    if (signal == SIGUSR2)
        strbit[i] = '1';
    i++;
    ft_printf("%s\n", strbit);
}

void    signal_manager(int signal)
{
    if (signal == SIGUSR1 || signal == SIGUSR2)
        decrypt_msg(signal);
}

void    set_signal_action(void)
{
    struct sigaction action;

    ft_bzero(&action, sizeof(action));
    action.sa_handler = &signal_manager;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
}

int main(void)
{
    pid_t serverpid;

    serverpid = getpid();
    ft_printf("%d\n", serverpid);

    set_signal_action();
    while (1)
        continue ;
    return (0);
}