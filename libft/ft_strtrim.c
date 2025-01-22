/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:55:53 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:03:06 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_instring(char const c, char const *set)
{
	size_t	idx;

	idx = 0;
	while (set[idx] != '\0')
	{
		if (c == set[idx])
			return (1);
		idx++;
	}
	return (0);
}

static int	ft_getlimits(char const *s1, char const *set, int s)
{
	size_t	idx;

	if (s == -1)
	{
		idx = ft_strlen(s1) - 1;
		while (idx > 0 && ft_instring(s1[idx], set))
			idx--;
		return (idx);
	}
	else if (s == 1)
	{
		idx = 0;
		while (s1[idx] != '\0' && ft_instring(s1[idx], set))
			idx++;
		return (idx);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	idx_str;
	size_t	idx_end;
	char	*nstr;
	size_t	nidx;

	if (!set || !s1)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	idx_str = ft_getlimits(s1, set, 1);
	idx_end = ft_getlimits(s1, set, -1);
	if (idx_str > idx_end)
		return (ft_strdup(""));
	nidx = 0;
	nstr = malloc(sizeof(char) * (idx_end - idx_str + 2));
	if (!nstr)
		return (NULL);
	while (idx_str <= idx_end)
	{
		nstr[nidx] = s1[idx_str];
		nidx++;
		idx_str++;
	}
	nstr[nidx] = '\0';
	return (nstr);
}
