#include "minitalk.h"

void    signal_handler(int  signum)
{
    printf("\nSignal sent\n");
}

void    set_SIGUSR1_action()
{
    struct sigaction sigusr1_action;
    sigusr1_action.sa_handler = signal_handler;
    sigemptyset(&sigusr1_action.sa_mask);
    sigusr1_action.sa_flags = 0;
    sigaction(SIGUSR1, &sigusr1_action, NULL);
}

int main(void)
{
    set_SIGUSR1_action();
    kill(serverpid, SIGUSR1);
    while (1)
        continue ;
    return (0);
}