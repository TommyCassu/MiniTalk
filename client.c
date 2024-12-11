/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:19:13 by tcassu            #+#    #+#             */
/*   Updated: 2024/12/11 14:52:14 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_client_reception;

void	handler(int signal)
{
	if (signal != SIGUSR1)
		return ;
	if (g_client_reception == 0)
		g_client_reception = 1;
}

int	get_power(int num)
{
	int	bit;

	bit = 1;
	while (num-- > 0)
		bit *= 2;
	return (bit);
}

void	ft_send_bits(int decimal, int pid)
{
	int	i;

	i = 8 - 1;
	while (i >= 0)
	{
		if (g_client_reception == 1)
			g_client_reception = 0;
		if (decimal >= get_power(i))
		{
			decimal -= get_power(i);
			kill(pid, SIGUSR1);
		}
		else
			kill(pid, SIGUSR2);
		i--;
		if (g_client_reception == -1)
			usleep(500);
		while (g_client_reception == 0)
		{
			sleep(1);
		}	
	}
}

void	ft_client_pid(int pid)
{
	char	*client_pid;
	int		i;

	i = 0;
	signal(SIGUSR1, handler);
	client_pid = ft_itoa(getpid());
	while (*(client_pid + i))
	{
		ft_send_bits(*(client_pid + i), pid);
		i++;
		usleep(800);
	}
	free(client_pid);
	ft_send_bits(0, pid);
	g_client_reception = 0;
}

int	main(int ac, char *av[])
{
	int	pid;
	int	i;

	if (ac != 3)
		return (0);
	g_client_reception = -1;
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (0);
	ft_client_pid(pid);
	i = 0;
	while (av[2][i])
	{
		ft_send_bits(av[2][i], pid);
		i++;
	}
	g_client_reception = -1;
	ft_send_bits(0, pid);
	exit(0);
	return (0);
}
