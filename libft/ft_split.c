/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:09:49 by nfelsemb          #+#    #+#             */
/*   Updated: 2021/11/30 15:12:26 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**tabvide(const char *s, char c)
{
	int		i;
	int		j;
	char	**de;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	de = malloc(sizeof(char *) * (j + 1));
	if (!de)
		return (0);
	de[j] = 0;
	return (de);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**dest;

	i = 0;
	k = 0;
	dest = tabvide(s, c);
	if (!dest)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[j] != c && s[j])
				j++;
			dest[k ++] = ft_substr(s, i, j - i);
			i = j - 1;
		}
		if (s[i + 1] == 0)
			break ;
		i++;
	}
	return (dest);
}
