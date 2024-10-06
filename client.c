/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:21:47 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/06 19:21:48 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_msg(pid_t serverpid, char c)
{
	int		i;
	char	temp_c;

	i = 7;
	while (i >= 0)
	{
		temp_c = c >> i;
		if ((temp_c >> 0 & 1) == 0)
			kill (serverpid, SIGUSR1);
		else
			kill(serverpid, SIGUSR2);
		usleep(425);
		i--;
	}
}

int	main(int argc, char *argv[])
{
	int	i;

	if (argc == 3)
	{
		i = 0;
		while (argv[2][i] != '\0')
		{
			send_msg(ft_atoi(argv[1]), argv[2][i]);
			i++;
		}
		send_msg(ft_atoi(argv[1]), '\0');
	}
	else
	{
		ft_printf("Error\n");
		return (1);
	}
	return (0);
}
