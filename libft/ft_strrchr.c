/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:30:34 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/30 12:59:21 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	if ((unsigned char)c == '\0')
	{
		return ((char *)s + len);
	}
	while (len >= 0)
	{
		if (s[len] == (unsigned char) c)
		{
			return ((char *)s + len);
		}
		len--;
	}
	return (0);
}
