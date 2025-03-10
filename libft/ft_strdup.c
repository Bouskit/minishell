/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:34:59 by xiazhang          #+#    #+#             */
/*   Updated: 2024/10/30 18:35:01 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	number;
	char	*ptr;
	char	*copy_ptr;

	number = ft_strlen(s);
	ptr = (char *)malloc((number + 1) * sizeof(char));
	copy_ptr = ptr;
	if (!ptr)
		return (NULL);
	while (*s)
	{
		*copy_ptr = *s;
		copy_ptr++;
		s++;
	}
	*copy_ptr = '\0';
	return (ptr);
}
