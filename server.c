/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:16:42 by tcassu            #+#    #+#             */
/*   Updated: 2024/12/07 21:07:06 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* ./server */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t bit_position = 0; // Position du bit en cours
volatile sig_atomic_t received_char = 0; // Caractère reçu

void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        // Mettre à 0 le bit correspondant
        received_char |= (0 << (7 - bit_position));
    } else if (sig == SIGUSR2) {
        // Mettre à 1 le bit correspondant
        received_char |= (1 << (7 - bit_position));
    }

    bit_position++;

    // Si tous les bits ont été reçus
    if (bit_position == 8) {
        printf("Caractère reçu : %c\n", received_char);
        fflush(stdout); // S'assurer que la sortie est affichée immédiatement
        // Réinitialiser pour le prochain caractère
        bit_position = 0;
        received_char = 0;
    }
}

int main() {
    // Définir les gestionnaires de signal
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Erreur lors de la définition du gestionnaire pour SIGUSR1");
        exit(EXIT_FAILURE);
    }
    
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Erreur lors de la définition du gestionnaire pour SIGUSR2");
        exit(EXIT_FAILURE);
    }
    printf("%d", getpid());
    printf("Serveur en attente de signaux...\n");
    
    while (1) {
        pause(); // Attendre un signal
    }

    return 0;
}











