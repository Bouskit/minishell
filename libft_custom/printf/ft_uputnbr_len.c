/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:49:36 by bboukach          #+#    #+#             */
/*   Updated: 2024/11/06 00:10:43 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_uputnbr_len(unsigned int nb, int *len)
{
	if (nb >= 10)
		ft_uputnbr_len(nb / 10, len);
	ft_putchar_len(nb % 10 + '0', len);
}
