/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:40 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:02:24 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static char	*ft_create_string(char *nstr, int n, int size)
{
	int	idx;

	idx = size;
	idx--;
	while (idx >= 0)
	{
		nstr[idx] = n % 10 + 48;
		n /= 10;
		idx--;
	}
	return (nstr);
}

char	*ft_itoa(int n)
{
	char	*nstr;
	int		len;
	int		is_ng;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n);
	is_ng = 0;
	nstr = malloc(sizeof(char) * (len + 1));
	if (!nstr)
		return (NULL);
	nstr[len] = 0;
	if (n < 0)
	{
		is_ng = 1;
		nstr[0] = '-';
		n *= -1;
	}
	ft_create_string(nstr + is_ng, n, len - is_ng);
	return (nstr);
}
