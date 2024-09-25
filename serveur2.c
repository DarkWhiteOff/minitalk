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

void	print_bits(unsigned char octet)
{
	int	i;
	unsigned char bit;

	i = 7;
	while (i >= 0)
	{
		bit = (octet >> i & 1) + '0';
        ft_printf("%c", bit);
		i--;
	}
    ft_printf("\n");
}

void    reset_vars()
{
    
}

void binary_to_decimal(int octet)
{
    int dec_value;
    int base;
    int temp;
    int last_digit;

    dec_value = 0;
    base = 1;
    temp = octet;
    last_digit = 0;
    while (temp)
    { 
        last_digit = temp % 10; 
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2; 
    }
    ft_printf("%c", dec_value);

}

void    decrypt_msg(unsigned char bit, int size)
{
    static int i;
    static unsigned char    *strbit;

    if (strbit == NULL)
        strbit = malloc(sizeof(unsigned char) * (size * 8) + 1);
    if (bit == '0')
        strbit[i++] = bit;
    else if (bit == '1')
        strbit[i++] = bit;
    if (i == size * 8)
    {
        int j;
        int k;
        unsigned char *bit;
        int octet;

        i = 0;
        while (i != size * 8)
        {
            j = i;
            k = 0;
            octet = 0;
            bit = malloc(sizeof(unsigned char) * 9);
            while (i < j + 8)
            {
                bit[k] = strbit[i];
                i++;
                k++;
            }
            bit[k] = '\0';
            octet = ft_atoi(bit);
            free(bit);
            binary_to_decimal(octet);
        }
        if (i == size * 8)
        {
            free(strbit);
            strbit == NULL;
            i = 0;
        }
    }
}

void    signal_manager(int signal)
{
    static int check = 1;
    static char c;
    static int size;
    static int counter;

    if (check == 1)
    {
        if (signal == SIGUSR1)
            c = '0';
        if (signal == SIGUSR2)
            c = '1';
        check = 0;
        return ;
    }
    if (c == '0')
    {
        if (signal == SIGUSR1)
            c = '3';
        if (signal == SIGUSR2)
        {
            size++;
            return ;
        }
    }
    if ( c == '1')
    {
        if (signal == SIGUSR1)
        {
            size++;
            return ;
        }
        if (signal == SIGUSR2)
            c = '3';
    }
    if (signal == SIGUSR1)
    {
        decrypt_msg('0', size);
        counter++;
        if (counter == size * 8)
        {
            check = 1;
            size = 0;
            counter = 0;
        }
    }
    if (signal == SIGUSR2)
    {
        decrypt_msg('1', size);
        counter++;
        if (counter == size * 8)
        {
            check = 1;
            size = 0;
            counter = 0;
        }
    }
}

int main(void)
{
    pid_t serverpid;

    signal(SIGUSR1, signal_manager);
    signal(SIGUSR2, signal_manager);
    serverpid = getpid();
    ft_printf("%d\n", serverpid);
    while (1)
        continue ;
    return (0);
}