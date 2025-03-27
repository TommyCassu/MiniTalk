/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:16:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/03/27 15:23:08 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

char	*g_line = NULL;

// Handler signal

static void	handle_complete_byte(int octet, siginfo_t *info)
{
	if (octet != '\0')
		g_line = ft_strjoinbis(g_line, octet);
	else
	{
		ft_putstr_fd(g_line, 1);
		free(g_line);
		g_line = NULL;
		kill(info->si_pid, SIGUSR2);
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int			octet = 0;
	static unsigned int	nbbits = 0;

	(void)context;
	if (!g_line)
		g_line = ft_strdup("");
	if (kill(info->si_pid, 0) < 0)
	{
		perror("Erreur de vérification du PID client");
		return ;
	}
	octet = (octet << 1) | (signum == SIGUSR1);
	if (++nbbits == 8)
	{
		handle_complete_byte(octet, info);
		nbbits = 0;
		octet = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

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

int	main(int ac, char *av[])
{
	int	pid;

	(void)av;
	if (ac == 1)
	{
		pid = getpid();
		ft_putstr_fd("PID : ", 1);
		ft_putnbr_fd(pid, 1);
		ft_putchar_fd('\n', 1);
		initialisation_sig(SIGUSR1, &signal_handler);
		initialisation_sig(SIGUSR2, &signal_handler);
		while (1)
			pause();
		free(g_line);
	}
	exit(1);
	return (0);
}
