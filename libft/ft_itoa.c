/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:24:38 by toto              #+#    #+#             */
/*   Updated: 2024/11/15 00:37:01 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countdigit(int nb)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		sign = 1;
		nb *= -1;
	}
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i + sign);
}

char	*ft_itoa(int nb)
{
	int		nbdigit;
	char	*result;
	int		sign;
	long	nbr;

	sign = 0;
	nbr = nb;
	nbdigit = ft_countdigit(nbr);
	result = (char *)malloc(sizeof(char) * (nbdigit + 1));
	if (!result)
		return (NULL);
	if (nbr < 0)
	{
		result[0] = '-';
		sign = 1;
		nbr *= -1;
	}
	result[nbdigit] = '\0';
	while (--nbdigit >= sign)
	{
		result[nbdigit] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (result);
}
