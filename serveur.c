#include "minitalk.h"

void    do_this()
{
    printf("\nSignal recieved\n");
}

int main(void)
{
    pid_t serverpid;

    serverpid = getpid();
    printf("%d\n", serverpid);
    signal(SIGUSR1, do_this);
    while (1)
        continue ;
    return (0);
}