/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:04:22 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/30 12:43:34 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		*sa;
	unsigned char		*sb;
	size_t				i;

	i = 0;
	sa = (unsigned char *) s1;
	sb = (unsigned char *) s2;
	while (i < n)
	{
		if (sa[i] != sb[i])
			return (sa[i] - sb[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (sa[i] - sb[i]);
}
