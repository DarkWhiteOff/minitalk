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

void	decimal_to_bits(unsigned char c, unsigned char *strbit, int msgsize)
{
	int	i;
	static int	j;

	i = 7;
	while (i >= 0)
	{
		strbit[j] = (c >> i & 1) + '0';
		i--;
		j++;
	}
	if (j == msgsize * 8)
		strbit[j] = '\0';
}

int main(int    argc, char  *argv[])
{
    pid_t   serverpid;
	int	msgsize;
	unsigned char	*strbit;
	int	i;
	char	c;

	serverpid = ft_atoi(argv[1]);
	msgsize = ft_strlen(argv[2]);
	strbit = malloc(sizeof(unsigned char) * msgsize * 8 + 1);
	i = 0;
	while (i < msgsize)
	{
		decimal_to_bits(argv[2][i], strbit, msgsize);
		i++;
	}
	i = 0;
	while (strbit[i] != '\0')
		i++;
	i = 0;
	if (strbit[i] == '0')
	{
		kill(serverpid, SIGUSR1);
		usleep(0);
		c = '0';
	}
	else if (strbit[i] == '1')
	{
		kill(serverpid, SIGUSR2);
		usleep(0);
		c = '1';
	}
	while (i < msgsize)
	{
		if (c == '0')
		{
			kill(serverpid, SIGUSR2);
			usleep(0);
		}
		else if (c == '1')
		{
			kill(serverpid, SIGUSR1);
			usleep(0);
		}
		i++;
	}
	i = 0;
	while (strbit[i] != '\0')
	{
		if (strbit[i] == '0')
		{
			kill(serverpid, SIGUSR1);
			usleep(0);
		}
		if (strbit[i] == '1')
		{
			kill(serverpid, SIGUSR2);
			usleep(0);
		}
		i++;
	}
    return (0);
}