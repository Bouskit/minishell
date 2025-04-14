/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:53:41 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/14 00:24:34 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h" // Or your relevant header
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
    char	*new_str;
    size_t	s1_len;
    size_t	s2_len;

    // Handle NULL input for s2 gracefully
    if (!s2)
        s2 = ""; // Treat NULL s2 as empty string
    s2_len = ft_strlen(s2);

    // *** CRITICAL PART: Handle s1 == NULL ***
    if (!s1)
    {
        // If s1 is NULL, behave like strdup(s2)
        s1 = ""; // Treat NULL s1 as empty string for length calculation
        s1_len = 0;
    }
    else
    {
        s1_len = ft_strlen(s1);
    }

    // Allocate memory
    new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (!new_str)
        return (NULL); // Allocation failed

    // Copy strings (using ft_memcpy or ft_strlcpy is safer)
    ft_memcpy(new_str, s1, s1_len);             // Copy s1 (or nothing if s1 was NULL)
    ft_memcpy(new_str + s1_len, s2, s2_len); // Copy s2 after s1
    new_str[s1_len + s2_len] = '\0';         // Null-terminate

    return (new_str);
}
/*int	main(void)
{
	char s1[] = "HELLO";
	char s2[] = "WORLD";
	printf("%s", ft_strjoin(s1, s2));
	return (0);
}*/