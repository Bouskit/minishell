/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:30:17 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/06 21:47:39 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbr, size_t size)
{
	unsigned char	*str;

	if (size != 0 && 65535 / size < nbr)
		return (NULL);
	str = malloc(size * nbr);
	if (!str)
		return (NULL);
	ft_memset(str, 0, nbr * size);
	return (str);
}

/*while (i < size * nbr)
	{
		str[i++] = 0;
	}*/