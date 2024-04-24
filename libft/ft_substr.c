/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.frn>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:17:34 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/01/12 07:29:58 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (start > ft_strlen(s))
		len = ft_strlen(s);
	else if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest || !s)
		return (0);
	if (start > ft_strlen(s))
		dest[0] = 0;
	else
		ft_strlcpy(dest, (char *)s + start, len + 1);
	return (dest);
}
