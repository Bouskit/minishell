/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:25:35 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/29 11:37:48 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tempdest;

	tempdest = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	while (n > 0)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		dest++;
		src++;
		n--;
	}
	return (tempdest);
}

/*int	main(void)
{
	//unsigned char dest[50];
	//ft_bzero(dest, 50);
	unsigned char  src[] = "Mandms";

	printf("%s", (unsigned char *)ft_memcpy(src + 1, src, 5));
	return (0);
}*/