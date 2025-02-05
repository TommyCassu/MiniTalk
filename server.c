/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:16:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/02/05 02:32:13 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
// Handler signal
void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int			octet = 0;
	static unsigned int	nbbits = 0;

	(void)context;
	if (kill(info->si_pid, 0) < 0)
	{
		perror("Erreur de vérification du PID client");
		return ;
	}
	octet = (octet << 1) | (signum == SIGUSR1);
	nbbits++;
	if (nbbits == 8 && octet != '\0')
	{
		ft_putchar_fd(octet, 1);
		nbbits = 0;
		octet = 0;
	}
	else if (octet == '\0' && nbbits == 8)
	{
		nbbits = 0;
		kill(info->si_pid, SIGUSR2);
	}
	kill(info->si_pid, SIGUSR1);
}

// Initialisation Signal
void	initialisation_sig(int sig, void (*signal_handler)
	(int, siginfo_t *, void *))
{
	struct sigaction	client;

	client.sa_sigaction = signal_handler;
	client.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigemptyset(&client.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &client, NULL);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &client, NULL);
}

int	main(void)
{
	int	pid;

	pid = getpid();
	printf("PID : %d\n", pid);
	initialisation_sig(SIGUSR1, &signal_handler);
	initialisation_sig(SIGUSR2, &signal_handler);
	while (1)
		pause();
	return (0);
}
