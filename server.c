/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:16:42 by tcassu            #+#    #+#             */
/*   Updated: 2024/12/11 14:54:24 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_storage	g_storage;

char	*update_content(char *current_content, char *new_data)
{
	char	*new_content;

	new_content = ft_strjoin(current_content, new_data);
	free(current_content);
	free(new_data);
	return (new_content);
}

int	ft_unbinary(int *binary)
{
	int	decimal;
	int	base;
	int	i;

	i = 7;
	base = 1;
	decimal = 0;
	while (i >= 0)
	{
		decimal += ((binary[i]) * base);
		i--;
		base *= 2;
	}
	return (decimal);
}

void	print_byte(int bits[])
{
	int		ascii;
	char	*decimal_str;

	ascii = 0;
	ascii = ft_unbinary(bits);
	decimal_str = ft_strdup((char *)&ascii);
	g_storage.content = update_content(g_storage.content, decimal_str);
	if (ascii == 0)
	{
		if (g_storage.c_pid == -1)
		{
			g_storage.c_pid = ft_atoi(g_storage.content);
			free(g_storage.content);
			g_storage.content = ft_strdup("");
			kill(g_storage.c_pid, SIGUSR1);
		}
		else
		{
			g_storage.c_pid = -1;
			printf(">> %s\n", g_storage.content);
			free(g_storage.content);
			g_storage.content = ft_strdup("");
		}
	}
}

void	add_bit(int signal)
{
	if (signal == SIGUSR1)
		g_storage.byte[g_storage.i] = 1;
	else if (signal == SIGUSR2)
		g_storage.byte[g_storage.i] = 0;
	else
		return ;
	g_storage.i++;
	if (g_storage.i >= 8)
	{
		g_storage.i = 0;
		print_byte(g_storage.byte);
	}
	if (g_storage.c_pid != -1)
		kill(g_storage.c_pid, SIGUSR1);
}

int	main(void)
{
	int	pid;

	pid = getpid();
	printf("__PID: %d\n", pid);
	g_storage.c_pid = -1;
	g_storage.content = ft_strdup("");
	signal(SIGUSR1, add_bit);
	signal(SIGUSR2, add_bit);
	while (1)
		sleep(1);
	if (*g_storage.content)
		free(g_storage.content);
	exit(0);
	return (0);
}