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

void	decimal_to_bits(unsigned char c, unsigned char *strbitok, int msgsize)
{
	int	i;
	static int	j;

	i = 7;
	while (i >= 0)
	{
		strbitok[j] = (c >> i & 1) + '0';
		i--;
		j++;
	}
	if (j == msgsize * 8)
		strbitok[j] = '\0';
}

int main(int    argc, char  *argv[])
{
    pid_t   serverpid;
	int	msgsize;
	unsigned char	*strbitok;
	int	i;
	int	c = 0;

	serverpid = ft_atoi(argv[1]);
	msgsize = ft_strlen(argv[2]);
	strbitok = malloc(sizeof(unsigned char) * msgsize * 8 + 1);
	i = 0;
	while (i < msgsize)
	{
		decimal_to_bits(argv[2][i], strbitok, msgsize);
		i++;
	}
	i = 0;
	if (strbitok[i] == '0')
	{
		kill(serverpid, SIGUSR1);
		usleep(6);
		c = 0;
		//ft_printf("First signal sent : SIGUSR1 -> c : %d\n", c);
	}
	else if (strbitok[i] == '1')
	{
		kill(serverpid, SIGUSR2);
		usleep(6);
		c = 1;
		//ft_printf("First signal sent : SIGUSR2 -> c : %d\n", c);
	}
	while (i < msgsize)
	{
		if (c == 0)
		{
			kill(serverpid, SIGUSR2);
			usleep(6);
			//ft_printf("Sending SIGUSR2 for size -> c : %d\n", c);
		}
		else if (c == 1)
		{
			kill(serverpid, SIGUSR1);
			usleep(6);
			//ft_printf("Sending SIGUSR1 for size -> c : %d\n", c);
		}
		i++;
	}
	i = 0;
	while (strbitok[i] != '\0')
	{
		if (strbitok[i] == '0')
		{
			kill(serverpid, SIGUSR1);
			usleep(6);
			//ft_printf("Sending SIGUSR1");
		}
		else if (strbitok[i] == '1')
		{
			kill(serverpid, SIGUSR2);
			usleep(6);
			//ft_printf("Sending SIGUSR2");
		}
		i++;
		//ft_printf(" i : %d\n", i);
	}
	free(strbitok);
	return (0);
}