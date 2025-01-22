/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:53:19 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:02:48 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	idx;
	size_t	len;
	char	*nstr;

	idx = 0;
	len = ft_strlen(s);
	nstr = malloc(sizeof(char) * (len + 1));
	if (!nstr)
		return (NULL);
	while (idx < len && s[idx])
	{
		nstr[idx] = s[idx];
		idx++;
	}
	nstr[idx] = 0;
	return (nstr);
}
