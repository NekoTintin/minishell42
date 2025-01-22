/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NekoTintin <tintin361official@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:56:14 by qupollet          #+#    #+#             */
/*   Updated: 2024/09/24 17:06:04 by NekoTintin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*nptr;
	int		counter;

	counter = 0;
	nptr = lst;
	while (nptr)
	{
		counter++;
		nptr = nptr->next;
	}
	return (counter);
}
