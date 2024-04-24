/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:56:29 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/29 17:10:56 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	lendst;
	unsigned int	lensrc;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	i = 0;
	if (lendst > dstsize)
		return (dstsize + lensrc);
	while (i + lendst + 1 < dstsize && src[i])
	{
		dst[i + lendst] = src[i];
		i++;
	}
	dst[i + lendst] = '\0';
	return (lendst + lensrc);
}
