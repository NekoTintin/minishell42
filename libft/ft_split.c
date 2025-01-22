/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:05:02 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:02:44 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getnbwords(char const *s, char c)
{
	int	idx;
	int	res;

	idx = 0;
	res = 0;
	while (s[idx] != '\0')
	{
		while (s[idx] == c)
			idx++;
		if (s[idx] != '\0')
		{
			res++;
			while (s[idx] != c && s[idx] != '\0')
				idx++;
		}
	}
	return (res);
}

static char	*ft_createstring(char const *s, int start, int end)
{
	char	*nstr;
	int		idx;
	int		len;

	idx = 0;
	len = end - start;
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!nstr)
		return (NULL);
	while (idx + start < end)
	{
		nstr[idx] = s[start + idx];
		idx++;
	}
	nstr[idx] = '\0';
	return (nstr);
}

static int	ft_iteratestring(char const *s, char c, char **str)
{
	size_t	t_idx;
	int		idx;
	int		idx2;

	t_idx = 0;
	idx = 0;
	while (s[idx] != '\0')
	{
		if (s[idx] != c)
		{
			idx2 = idx;
			while (s[idx2] != c && s[idx2] != 0)
				idx2++;
			str[t_idx] = ft_createstring(s, idx, idx2);
			if (!str[t_idx])
				return (1);
			t_idx++;
			idx = idx2;
		}
		else
			idx++;
	}
	str[t_idx] = NULL;
	return (0);
}

static void	ft_freemalloc(char **str, size_t size)
{
	size_t	t_idx;

	t_idx = 0;
	while (t_idx < size)
	{
		if (str[t_idx])
			free(str[t_idx]);
		t_idx++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		nb_words;
	char	**tab;

	if (!s)
		return (NULL);
	nb_words = ft_getnbwords(s, c);
	tab = (char **)ft_calloc(sizeof(char *), nb_words + 1);
	if (!tab)
		return (NULL);
	if (ft_iteratestring(s, c, tab) == 1)
	{
		ft_freemalloc(tab, nb_words + 1);
		return (NULL);
	}
	return (tab);
}
