/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:40:49 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/26 15:39:53 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	longu(long int num)
{
	int	lon;

	lon = 0;
	if (num < 0)
	{
		num = -num;
		lon++;
	}
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 10;
		lon++;
	}
	return (lon);
}

char	*check(char *ds, long int nb)
{
	if (!ds)
		return (0);
	if (nb == 0)
	{
		ds[0] = 48;
		ds[1] = 0;
		return (ds);
	}
	ds[0] = 'a';
	return (ds);
}

char	*ft_itoa(int n)
{
	char		*dest;
	int			i;
	long int	na;

	na = n;
	i = longu(na);
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (0);
	if (check(dest, na)[0] != 'a')
		return (check(dest, na));
	dest[i--] = 0;
	if (na < 0)
	{
		dest[0] = '-';
		na = -na;
	}
	while (na > 0)
	{
		dest[i--] = (na % 10) + 48;
		na = na / 10;
	}
	return (dest);
}
