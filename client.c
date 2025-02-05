/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:19:13 by tcassu            #+#    #+#             */
/*   Updated: 2025/02/05 02:45:05 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bit_control;

void	send_char(char c, pid_t pid)
{
	int	bit;

	bit = 8 * sizeof(c) - 1;
	while (bit >= 0)
	{
		if (kill(pid, 0) < 0)
		{
			printf("ERROR : cant send sig to pid : %d\n", pid);
			exit(EXIT_FAILURE);
		}
		g_bit_control = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		while (g_bit_control != 1)
			usleep(10);
	}
}

void	send_str(char *str, pid_t pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(str[i], pid);
		i++;
	}
	send_char('\n', pid);
	send_char(0, pid);
}

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_bit_control = 1;
	else if (sig == SIGUSR2)
	{
		printf("Message received !\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		printf("Usage : ./client <pid> <Chaîne de caractères à transmettre>\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, &signal_handler);
	signal(SIGUSR2, &signal_handler);
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		printf("Veuillez veuillez vérifier le PID envoyé\n");
		exit(EXIT_FAILURE);
	}
	send_str(argv[2], pid);
	while (1)
		sleep(1);
}
