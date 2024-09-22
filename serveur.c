#include "minitalk.h"

void    signal_manager(int signal)
{
    int msgsize;

    msgsize = 0;
    if (signal == SIGUSR1)
        msgsize++;
    ft_printf("%d\n", msgsize);

}

int main(void)
{
    pid_t serverpid;
    struct sigaction action_sigusr1;

    serverpid = getpid();
    ft_printf("%d\n", serverpid);
    action_sigusr1.sa_handler = signal_manager;
    sigemptyset(&action_sigusr1.sa_mask);
    action_sigusr1.sa_flags = 0;
    sigaction(SIGUSR1, &action_sigusr1, NULL);
    while (1)
        continue ;
    return (0);
}