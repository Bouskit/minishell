/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:37:21 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/29 23:52:15 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < dstsize && dst[i])
	{
		i++;
	}
	while ((i + j + 1) < dstsize && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i != dstsize)
	{
		dst[i + j] = '\0';
	}
	return (i + ft_strlen(src));
}

/*
int	main(void)
{
	char dst[20] = "Hello";
	const char src[] = "World";

	printf("avant : %s\n", dst);
	ft_strlcat(dst, src, 9);
	printf("copie de dst : %s", dst);
	return (0);
}*/