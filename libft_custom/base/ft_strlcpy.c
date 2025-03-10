/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:44:17 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/24 23:12:17 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (src_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

/*int	main(void)
{
	char dst[20] = "Hello";
	const char src[] = "World";

	printf("avant dst = %s\n", dst);
	ft_strlcpy(dst, src, 3);
	printf("après dst = %s", dst);
	return (0);
}*/