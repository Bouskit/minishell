/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:34:07 by bboukach          #+#    #+#             */
/*   Updated: 2024/11/06 00:09:52 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_len(int nb, int *len)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		*len += 11;
		return ;
	}
	if (nb < 0)
	{
		ft_putchar_len('-', len);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_len(nb / 10, len);
		ft_putnbr_len(nb % 10, len);
	}
	else
		ft_putchar_len(nb + '0', len);
}
