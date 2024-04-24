/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:04:47 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/25 11:11:18 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skipspace(char *sr)
{
	int	j;

	j = 0;
	while ((sr[j] >= 9 && sr[j] <= 13) || sr[j] == ' ')
		j++;
	return (j);
}

int	ft_atoi(const char *tab)
{
	int	res;
	int	i;
	int	neg;

	res = 0;
	i = 0;
	neg = 1;
	i = skipspace((char *)tab);
	if (tab[i] == '-' || tab[i] == '+')
	{
		if (tab[i] == '-')
			neg = -1;
		i++;
	}
	while (tab[i])
	{
		if (ft_isdigit(tab[i]))
		{
			res = res * 10 + (tab[i] - 48);
		}
		else
			return (res * neg);
		i++;
	}
	return (res * neg);
}
