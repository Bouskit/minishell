/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:41:26 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/24 22:49:26 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*strcpy;
	size_t	i;

	i = 0;
	strcpy = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!strcpy)
		return (NULL);
	while (str[i])
	{
		strcpy[i] = str[i];
		i++;
	}
	strcpy[i] = '\0';
	return (strcpy);
}

/*int main()
{
	char str[] = "Hello";
	printf("dest :%s", ft_strdup(str));
	return (0);
}*/