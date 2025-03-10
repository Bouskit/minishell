/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:52:46 by bboukach          #+#    #+#             */
/*   Updated: 2024/11/06 00:09:18 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hexa_len(unsigned long long nbr, const char *alpha, int *len)
{
	if (nbr >= 16)
	{
		ft_hexa_len(nbr / 16, alpha, len);
		ft_hexa_len(nbr % 16, alpha, len);
	}
	else
		ft_putchar_len(alpha[nbr % 16], len);
}
