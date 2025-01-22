/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:40:19 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:02:36 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_ptr_len(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr != 0)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}

int	ft_print_ptr(const void *ptr)
{
	uintptr_t	addr;
	char		*res;
	char		*char_set;
	int			idx;
	int			count;

	count = 0;
	addr = (uintptr_t)ptr;
	if (addr == 0)
		return (ft_putstr_fd("(nil)", 1));
	idx = ft_get_ptr_len(addr);
	res = (char *)ft_calloc(idx + 3, sizeof(char));
	if (!res)
		return (0);
	char_set = "0123456789abcdef";
	while (addr != 0)
	{
		res[--idx] = char_set[addr % 16];
		addr /= 16;
		count++;
	}
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(res + idx, 1);
	free(res);
	return (count + 2);
}

int	ft_selectformat(char format, va_list arg_list)
{
	if (format == '%')
		return (ft_putchar_fd('%', 1));
	else if (format == 'c')
		return (ft_putchar_fd(va_arg(arg_list, int), 1));
	else if (format == 's')
		return (ft_putstr_fd(va_arg(arg_list, char *), 1));
	else if (format == 'i' || format == 'd')
		return (ft_print_nbr(va_arg(arg_list, int)));
	else if (format == 'x' || format == 'X')
		return (ft_print_hexa(va_arg(arg_list, int), format));
	else if (format == 'u')
		return (ft_print_udecimal(va_arg(arg_list, unsigned int)));
	else if (format == 'p')
		return (ft_print_ptr(va_arg(arg_list, void *)));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list			arg_list;
	int				idx;
	unsigned int	nb_char;

	if (str == NULL)
		return (-1);
	va_start(arg_list, str);
	idx = 0;
	nb_char = 0;
	while (str[idx] != 0)
	{
		if (str[idx] == '%')
		{
			if (str[idx + 1] == 0)
				return (va_end(arg_list), -1);
			nb_char += ft_selectformat(str[idx + 1], arg_list);
			idx++;
		}
		else
			nb_char += ft_putchar_fd(str[idx], 1);
		idx++;
	}
	va_end(arg_list);
	return (nb_char);
}
