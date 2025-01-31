/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:19:13 by tcassu            #+#    #+#             */
/*   Updated: 2025/01/31 02:26:08 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    ft_send_bits(int pid, char *str)
{
    int i;
    int bit;
    
    i = 0;
    while(str[i])
    {
        bit = 7;
        while (bit >= 0)
        {
            if (((str[i] >> bit) & 1) == 1)
                kill(pid, SIGUSR2);
            else
                kill(pid, SIGUSR1);
            usleep(42);
            bit--;
        }
        i++;
    }
}

int main(int ac, char *av[])
{
    int pid;
    
    (void)ac;
    pid = ft_atoi(av[1]);
    ft_send_bits(pid, av[2]);
}
