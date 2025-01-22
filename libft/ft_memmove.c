/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:53:43 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:02:32 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			idx;
	unsigned char	*dst;
	unsigned char	*sc;

	if (!dest && !src)
		return (NULL);
	dst = (unsigned char *)dest;
	sc = (unsigned char *)src;
	idx = 0;
	if (dst > sc)
	{
		while (n-- > 0)
			dst[n] = sc[n];
	}
	else
	{
		while (idx < n)
		{
			dst[idx] = sc[idx];
			idx++;
		}
	}
	return (dest);
}
