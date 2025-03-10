/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:10:31 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/29 11:43:26 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*tempdest;
	unsigned char	*tempsrc;

	tempdest = (unsigned char *)dest;
	tempsrc = (unsigned char *)src;
	if (!dest && !src)
		return (tempdest);
	if (dest > src)
		while (len--)
			tempdest[len] = tempsrc[len];
	else
	{
		while (len--)
		{
			*tempdest = *tempsrc;
			tempdest++;
			tempsrc++;
		}
	}
	return (dest);
}
/*int	main(void)
{
	//unsigned char dest[50];
	//ft_bzero(dest, 50);
	unsigned char  src[] = "Mandms";

	printf("%s", (unsigned char *)ft_memmove(src + 1, src, 5));
	return (0);
}*/