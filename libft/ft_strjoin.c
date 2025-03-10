/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:35:35 by xiazhang          #+#    #+#             */
/*   Updated: 2024/10/30 18:35:37 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)//function
{
	int		lens1;
	int		lens2;
	char	*ptr;
	char	*copy_ptr;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	ptr = (char *)malloc((lens1 + lens2 + 1) * sizeof(char));
	copy_ptr = ptr;
	if (!ptr)
		return (NULL);
	while (*s1)
	{
		*copy_ptr = *s1;
		copy_ptr++;
		s1++;
	}
	while (*s2)
	{
		*copy_ptr = *s2;
		copy_ptr++;
		s2++;
	}
	*copy_ptr = '\0';
	return (ptr);
}
