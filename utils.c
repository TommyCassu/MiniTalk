/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:12:22 by tcassu            #+#    #+#             */
/*   Updated: 2025/03/27 15:17:10 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlenbis(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoinbis(char *s1, char s2)
{
	int		i;
	int		size;
	char	*result;

	i = 0;
	size = ft_strlenbis(s1) + 1;
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = s2;
	result[i] = '\0';
	free(s1);
	return (result);
}
