/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:59:24 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/30 12:26:58 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*occ;
	char	cc;

	i = 0;
	occ = NULL;
	cc = (char)c;
	while (str[i])
	{
		if (str[i] == cc)
			occ = (char *)&str[i];
		i++;
	}
	if (str[i] == cc)
		occ = (char *)&str[i];
	return (occ);
}

/*int main()
{
	char str[] = "Melvpin le petit bourgeois";
	int	c = 0;
	printf("res : %s", ft_strrchr(str,c));
	return (0);
}*/