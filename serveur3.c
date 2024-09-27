#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

void    binary_to_decimal(char *octet)
{
    int somme;
    int i;
    int val_bi;
    char letter;

    i = 0;
    val_bi = 128;
    somme = 0;
    while(octet[i])
    {
        if(octet[i] == '1')
            somme += val_bi;
        val_bi /= 2;
        i++;
    }
	ft_printf("%c", somme);
}

void    signal_manager(int signal)
{
    static int  i;
    static char *octet;

    if (octet == NULL)
        octet = malloc(sizeof(char) * 9);
    if (signal == SIGUSR1)
        octet[i++] = '0';
    else if (signal == SIGUSR2)
        octet[i++] = '1';
    if (i == 8)
    {
        octet[8] = '\0';
        binary_to_decimal(octet);
        i = 0;
        free(octet);
        octet = NULL;
    }
}

int main(void)
{
    pid_t serverpid;

    serverpid = getpid();
    ft_printf("Server ID : %d\n", serverpid);
    signal(SIGUSR1, signal_manager);
    signal(SIGUSR2, signal_manager);
    while (1)
        pause();
    return (0);
}