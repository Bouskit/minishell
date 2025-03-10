/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:44:00 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/23 22:00:34 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t len)
{
	unsigned char	*temp;
	size_t			i;

	temp = (unsigned char *)str;
	i = 0;
	while (len > 0)
	{
		temp[i] = (unsigned char)value;
		i++;
		len--;
	}
	return (str);
}

/*int main()
{
	unsigned char str[] = "Hello";
	printf("rep :%s\n", (unsigned char *)ft_memset(str,'0',ft_strlen(str)));
	return (0);
}*/