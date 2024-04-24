/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:43:50 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/24 11:43:52 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*de;
	char	*sr;
	size_t	i;

	de = (char *)dest;
	sr = (char *)src;
	i = 0;
	if (de > sr)
	{
		while (n > 0)
		{
			n--;
			de[n] = sr[n];
		}
	}
	else
	{
		while (i < n)
		{
			de[i] = sr[i];
			i++;
		}
	}
	return (dest);
}
