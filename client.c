/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:19:13 by tcassu            #+#    #+#             */
/*   Updated: 2024/12/07 21:16:50 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* ./client PID "MESSAGE" */


void	ft_send_bit(int pid, int bit)
{
	if (bit == 1)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
    usleep(100);
}
void	ft_send_char (int pid, char c)
{
	int i;

	i = 7;
	while (i >= 0)
	{
		ft_send_bit(pid, (c >> i)&1);
		i--;
	}
	printf("\n");
}

void	ft_send_string(int pid, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_send_char(pid, str[i]);
		i++;
	}
}
int	main(int ac, char *av[])
{
	int		pid;
	size_t	i;
	int		length;
	int		sleep;

	if (ac != 3)
		return (0);
	pid = atoi(av[1]);
	if (pid <= 0)
        return (0);
	ft_send_string(pid, av[2]);
    
}