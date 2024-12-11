/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:59:18 by toto              #+#    #+#             */
/*   Updated: 2024/11/23 00:03:10 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
}

int	ft_countword(const char *str, char c)
{
	int	i;
	int	inword;
	int	nbword;

	i = 0;
	inword = 0;
	nbword = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			inword = 0;
		else if (str[i] != c && inword == 0)
		{
			inword = 1;
			nbword++;
		}
		i++;
	}
	return (nbword);
}

char	*ft_strcpy(const char *src, char *dest, int debut, int fin)
{
	int	i;

	i = 0;
	while (debut <= fin)
	{
		dest[i] = src[debut];
		i++;
		debut++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_set_string(const char *str, char **result, char c)
{
	int		i;
	int		debut;
	int		aw;

	i = 0;
	aw = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		debut = i;
		while (str[i] != c && str[i] != '\0')
			i++;
		if (aw < ft_countword(str, c))
		{
			result[aw] = (char *)malloc(sizeof(char) * ((i - 1)
						- debut + 1) + 1);
			if (!result[aw])
				return (NULL);
			result[aw] = ft_strcpy(str, result[aw], debut, (i - 1));
			aw++;
		}
	}
	result[aw] = 0;
	return (result);
}

char	**ft_split(char const *str, char c)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (ft_countword(str, c) + 1));
	if (!result)
		return (NULL);
	if (!ft_set_string(str, result, c))
	{
		ft_free(result);
		free(result);
		return (NULL);
	}
	return (result);
}
