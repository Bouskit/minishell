/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:06:07 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/30 12:27:24 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *mot, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str && !len)
		return (NULL);
	if (*mot == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		while (str[i + j] == mot[j] && mot[j] && i + j < len)
		{
			j++;
			if (mot[j] == '\0')
				return ((char *)str + i);
		}
		i++;
		j = 0;
	}
	return (NULL);
}
/*int	main(void)
{
	char str[] = "Melprovin prout caca zizi";
	char mot[] = "prout";
	printf("%s", ft_strnstr(str, mot, 4));
	return (0);
}*/