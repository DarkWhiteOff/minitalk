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

char	*decimal_to_bits(char *octet, char c)
{
	int	i;
	int	j;

	i = 7;
	j = 0;
	while (i >= 0)
	{
		octet[j] = (c >> i & 1) + '0';
		i--;
		j++;
	}
	octet[j] = '\0';
	return (octet);
}

void	send_msg(pid_t serverpid, char *msg)
{
	int	i;
	int	j;
	char	*octet;

	i = 0;
	j = 0;
	while (msg[i] != '\0')
	{
		octet = malloc(sizeof(char) * 9);
		octet = decimal_to_bits(octet, msg[i]);
		while (octet[j] != '\0')
		{
			if (octet[j] == '0')
				kill(serverpid, SIGUSR1);
			else if (octet[j] == '1')
				kill(serverpid, SIGUSR2);
			usleep(200);
			j++;
		}
		free(octet);
		j = 0;
		i++;
	}
}

int main(int    argc, char  *argv[])
{
    send_msg(ft_atoi(argv[1]), argv[2]);
	return (0);
}