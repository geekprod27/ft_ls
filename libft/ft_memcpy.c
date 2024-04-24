/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:43:50 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/29 18:32:29 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*de;

	de = (char *)dest;
	while (n > 0)
	{
		*(char *)dest = *(char *) src;
		src++;
		dest++;
		n--;
	}
	return (de);
}
