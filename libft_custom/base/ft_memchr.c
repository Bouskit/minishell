/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:31:09 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/29 14:55:10 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*str;

	uc = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == uc)
			return ((void *)&str[i]);
		i++;
	}
	return (0);
}
/*int main()
{
	char str[] = "Melvin le petit bourgeois";
	int	c = 'p';
	printf("res : %p", ft_memchr(str, c, 25));
	return (0);
}*/