/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:26:29 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/24 17:20:39 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *s)
{
	int	lenght;
	int	index;

	if (!s)
		return (0);
	lenght = 0;
	index = -1;
	while (s[++index] != '\0')
		lenght++;
	return (lenght);
}
