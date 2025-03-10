/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:10:30 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/22 17:36:58 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}

/*int main()
{
	unsigned char str[] = "Hello";
	ft_bzero(str, ft_strlen(str));
	printf("str est : %s", str);
	return (0);
}*/