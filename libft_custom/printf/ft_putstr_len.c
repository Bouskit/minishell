/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:34:37 by bboukach          #+#    #+#             */
/*   Updated: 2024/11/06 00:11:35 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_len(char *str, int *len)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr_len("(null)", len));
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
		(*len)++;
	}
}
