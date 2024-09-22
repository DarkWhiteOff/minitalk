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

int main(int    argc, char  *argv[])
{
    pid_t   serverpid;
	char	*message;
	int	msgsize;

    serverpid = ft_atoi(argv[1]);
	message = argv[2];
	msgsize = ft_strlen(argv[2]);
	while (msgsize--)
    	kill(serverpid, SIGUSR1);
    while (1)
        continue ;
    return (0);
}