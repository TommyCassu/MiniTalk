/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:25:46 by marvin            #+#    #+#             */
/*   Updated: 2024/11/11 00:39:16 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	sizedst;
	size_t	sizesrc;
	size_t	i;

	sizedst = ft_strlen(dst);
	sizesrc = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (sizesrc);
	while (src[i] != '\0' && (i + sizedst + 1) < size)
	{
		dst[i + sizedst] = src[i];
		i++;
	}
	dst[i + sizedst] = '\0';
	if (sizedst >= size)
		sizedst = size;
	return (sizedst + sizesrc);
}
