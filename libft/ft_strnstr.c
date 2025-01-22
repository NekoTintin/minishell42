/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:24:24 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:03:02 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b_idx;
	size_t	l_idx;
	size_t	little_size;

	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	b_idx = 0;
	little_size = ft_strlen(little) - 1;
	while (big[b_idx] != 0 && b_idx < len)
	{
		l_idx = 0;
		if (big[b_idx] == little[l_idx])
		{
			while (little[l_idx] && big[b_idx + l_idx] == little[l_idx])
			{
				if (l_idx == little_size && b_idx + l_idx < len)
					return ((char *)&big[b_idx]);
				l_idx++;
			}
		}
		b_idx++;
	}
	return (NULL);
}
