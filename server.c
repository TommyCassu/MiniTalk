/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:16:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/01/31 02:35:02 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
// Handler signal
void signal_handler(int signum, siginfo_t *info, void *context)
{
    static int octet = 0;
    static unsigned int nbBits = 0;
    
    (void)context;
    //printf("Signal reçu: %s, Bit: %d\n", signum == SIGUSR1 ? "SIGUSR1" : "SIGUSR2", nbBits);
    
    if (kill(info->si_pid, 0) < 0)
    {
        perror("Erreur de vérification du PID client");
        return;
    }
    
    if (signum == SIGUSR1)
		octet = (octet << 1);
	if (signum == SIGUSR2)
		octet = (octet << 1) |1;
    nbBits++;
    if (nbBits == 8)
    {
        printf("qweeqwe qweqweqwe %c\n", octet);
        nbBits = 0;
        octet = 0;
    }
}

// Initialisation Signal

void	initialisation_sig(int sig, void (*signal_handler)(int, siginfo_t *, void *))
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
	// Header
	print_header();
	pid = getpid();
	printf("                      %d\n", pid);
	// Signal
	initialisation_sig(SIGUSR1, &signal_handler);
	initialisation_sig(SIGUSR2, &signal_handler);
	while (1)
		pause();
	return (0);
}