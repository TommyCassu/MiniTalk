/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:37:22 by toto              #+#    #+#             */
/*   Updated: 2024/11/23 01:00:10 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	sizelittle;
	size_t	i;
	size_t	j;

	i = 0;
	if (big == NULL)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	sizelittle = ft_strlen(little);
	if (sizelittle > len)
		return (NULL);
	while (big[i] != '\0' && i <= len - sizelittle)
	{
		j = 0;
		while (big[i + j] == little[j] && j < sizelittle)
			j++;
		if (j == sizelittle)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
