/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:06:22 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/30 17:52:05 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isd(char c, char const *d)
{
	int	i;

	i = 0;
	while (d[i])
	{
		if (d[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	count(char const *s1, char const *set)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (!isd(s1[i], set))
	{
		i++;
		count++;
	}
	if (!s1[i])
		return (count);
	while (s1[i])
		i++;
	i--;
	while (!isd(s1[i], set))
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s1) + 1 - count(s1, set)));
	if (!dest)
		return (0);
	while (!isd(s1[i], set))
		i++;
	if (!s1[i])
	{
		dest[0] = '\0';
		return (dest);
	}
	while (s1[i] && j < (int)ft_strlen(s1) - (int)count(s1, set))
		dest[j++] = s1[i++];
	dest[j] = '\0';
	return (dest);
}
