/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:21:03 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:03:14 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_char_set(char state)
{
	if (state == 'X')
		return ("0123456789ABCDEF");
	else
		return ("0123456789abcdef");
}

int	ft_print_hexa(unsigned int nbr, char state)
{
	char			*res;
	char			*char_set;
	int				idx;
	int				count;

	count = 0;
	if (nbr == 0)
		return (ft_putchar_fd('0', 1));
	char_set = ft_char_set(state);
	res = (char *)ft_calloc(9, sizeof(char));
	if (!res)
		return (0);
	idx = 8;
	while (nbr != 0)
	{
		res[--idx] = char_set[nbr % 16];
		nbr /= 16;
		count++;
	}
	ft_putstr_fd(res + idx, 1);
	free(res);
	return (count);
}

int	ft_print_udecimal(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr <= 9)
	{
		ft_putchar_fd(48 + nbr, 1);
		count++;
		return (count);
	}
	if (nbr != 0)
		count += ft_print_udecimal(nbr / 10);
	count++;
	ft_putchar_fd((nbr % 10) + 48, 1);
	return (count);
}

int	ft_print_nbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (11);
	}
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		count++;
		n *= -1;
	}
	if (n >= 0 && n <= 9)
	{
		ft_putchar_fd(48 + n, 1);
		count++;
		return (count);
	}
	if (n != 0)
		count += ft_print_nbr(n / 10);
	ft_putchar_fd((n % 10) + 48, 1);
	count++;
	return (count);
}
