/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:16:08 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:02:55 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	idx;

	idx = 0;
	if (siz > 0)
	{
		while (src[idx] && idx < siz - 1)
		{
			dst[idx] = src[idx];
			idx++;
		}
		dst[idx] = 0;
	}
	while (src[idx])
		idx++;
	return (idx);
}
