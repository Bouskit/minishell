/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:32:10 by xiazhang          #+#    #+#             */
/*   Updated: 2025/03/08 21:32:12 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}


