/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:18:18 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:03:08 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*nstr;
	size_t	s_idx;
	size_t	nstr_idx;

	if (s)
	{
		if (start > (unsigned int)ft_strlen(s))
			return (ft_strdup(""));
		s_idx = start;
		nstr_idx = 0;
		if (len > (size_t)ft_strlen(s + start))
			len = (size_t)ft_strlen(s + start);
		nstr = malloc(sizeof(char) * len + 1);
		if (!nstr)
			return (NULL);
		while (s[s_idx] && nstr_idx < len)
		{
			nstr[nstr_idx] = s[s_idx];
			nstr_idx++;
			s_idx++;
		}
		nstr[nstr_idx] = 0;
		return (nstr);
	}
	return (0);
}
