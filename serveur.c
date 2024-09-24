#include "minitalk.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ss;
	char	*dest;

	i = 0;
	ss = (char *)s;
	while (ss[i] != '\0')
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (ss[i] != '\0')
	{
		dest[i] = ss[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void    decrypt_msg(int signal)
{
    static int i;
    static unsigned char    *strbit;

    strbit = ft_strdup("");
    if (signal == SIGUSR1)
        strbit[i++] = '0';
    else if (signal == SIGUSR2)
        strbit[i++] = '1';
    ft_printf("%s\n", strbit);
}

void    signal_manager(int signal)
{
    static int j;

    if (j <= 8)
    {
        if (signal == SIGUSR1 || signal == SIGUSR2)
        {
            ft_printf("caca");
            decrypt_msg(signal);
            j++;
        }
    }
}

int main(void)
{
    struct sigaction    action;
    pid_t serverpid;

    action.sa_handler = &signal_manager;
    action.sa_flags = 0;
    serverpid = getpid();
    ft_printf("%d\n", serverpid);
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while (1)
        continue ;
    return (0);
}