/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:00:05 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/29 17:10:46 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		lens;
	char	*ptr;

	i = 0;
	lens = ft_strlen(s);
	ptr = malloc(sizeof(char) * lens + 1);
	if (!ptr)
		return (0);
	while (i < lens)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
