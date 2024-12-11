/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:59:10 by toto              #+#    #+#             */
/*   Updated: 2024/11/22 22:33:51 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*memory;

	memory = (void *)malloc(size * nmemb);
	if (!memory)
		return (NULL);
	ft_bzero(memory, size * nmemb);
	return (memory);
}
