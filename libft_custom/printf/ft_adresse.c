/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adresse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:59:20 by bboukach          #+#    #+#             */
/*   Updated: 2024/11/06 00:10:34 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_adresse(unsigned long long ptr, int *len)
{
	if (ptr == 0)
	{
		ft_putstr_len("(nil)", len);
		return ;
	}
	else
	{
		ft_putstr_len("0x", len);
		ft_hexa_len(ptr, "0123456789abcdef", len);
	}
}
