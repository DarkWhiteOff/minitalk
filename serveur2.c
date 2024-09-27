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
        //ft_printf("%c", bit);
		i--;
	}
    //ft_printf("\n");
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

/* int l = 0;
    while (l < i)
    {
        write(1, &strbit[l], 1);
        l++;
    } */
////ft_printf("strbit : %s\n", strbit);

void    decrypt_msg(unsigned char bit, int size)
{
    static int i;
    static unsigned char    *strbit;
    int k;
    unsigned char *octet;
    int octet2;

    if (strbit == NULL)
        strbit = malloc(sizeof(unsigned char) * (size * 8) + 1);
    if (bit == '0')
        strbit[i++] = bit;
    else if (bit == '1')
        strbit[i++] = bit;
    if (i == size * 8)
    {
        //ft_printf("i when entering : %d\n", i);
        strbit[i] = '\0';
        i = 0;
        while (strbit[i] != '\0')
        {
            k = 0;
            octet2 = 0;
            octet = malloc(sizeof(unsigned char) * 9);
            while (k < 8)
            {
                octet[k] = strbit[i];
                i++;
                k++;
            }
            octet[k] = '\0';
            octet2 = ft_atoi(octet);
            free(octet);
            //ft_printf("octet2 : %d ", octet2);
            binary_to_decimal(octet2);
        }
        //ft_printf("i when leaving : %d\n", i);
        //ft_printf("strbit when leaving : %s\n", strbit);
        ft_printf("\n");
        free(strbit);
        strbit = NULL;
        i = 0;
    }
}

void    signal_manager(int signal)
{
    static int check = 1;
    static int c = 4;
    static int size;
    static int counter;

    if (check == 1)
    {
        if (signal == SIGUSR1)
            c = 0;
        if (signal == SIGUSR2)
            c = 1;
        check = 0;
        //ft_printf("Checking first signal -> c : %d / size : %d / check : %d\n", c, size, check);
        return ;
    }
    if (c == 0)
    {
        if (signal == SIGUSR2)
        {
            size++;
            //ft_printf("SIGUSR2 recieved -> c : %d / check : %d\n", c, check);
            return ;
        }
        else if (signal == SIGUSR1)
        {
            c = 3;
            //ft_printf("SIGUSR1 recieved -> c : %d / check : %d\n", c, check);
        }
    }
    else if (c == 1)
    {
        if (signal == SIGUSR1)
        {
            size++;
            return ;
        }
        else if (signal == SIGUSR2)
            c = 3;
    }
    //ft_printf("size : %d\n", size);
    if (signal == SIGUSR1)
    {
        decrypt_msg('0', size);
        counter++;
        //ft_printf("SIGUSR1 recieved -> counter : %d\n", counter);
        if (counter == size * 8)
        {
            //ft_printf("Reset vars entred\n");
            check = 1;
            c = 4;
            size = 0;
            counter = 0;
            //ft_printf("Checking vars -> check : %d / c : %d / size : %d / counter : %d\n", check, c, size, counter);
            //ft_printf("Exiting process\n");
            usleep(6);
            //exit(0);
        }
    }
    else if (signal == SIGUSR2)
    {
        decrypt_msg('1', size);
        counter++;
        //ft_printf("SIGUSR2 recieved -> counter : %d\n", counter);
        if (counter == size * 8)
        {
            //ft_printf("Reset vars entred\n");
            check = 1;
            size = 0;
            counter = 0;
            //ft_printf("Checking vars -> check : %d / c : %d / size : %d / counter : %d\n", check, c, size, counter);
            //ft_printf("Exiting process\n");
            usleep(6);
            //exit(0);
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