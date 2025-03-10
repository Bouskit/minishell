/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:23:06 by bboukach          #+#    #+#             */
/*   Updated: 2024/10/30 12:28:10 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*s;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		len = 0;
	else if (len > ft_strlen(str) - start)
		len = ft_strlen(str) - start;
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	while (i < len && start + i < ft_strlen(str))
	{
		s[i] = str[start + i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

/*int main ()
{
	char str[] = "Bonjour comment ça va";
	printf ("%s", ft_substr(str, 5, 8));
	return (0);
}*/