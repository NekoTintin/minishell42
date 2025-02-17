/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:53:19 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/17 13:15:30 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	idx;
	size_t	len;
	char	*nstr;

	if (!s)
		return (NULL);
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
