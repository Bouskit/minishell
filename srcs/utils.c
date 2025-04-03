/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:50:27 by xiazhang          #+#    #+#             */
/*   Updated: 2025/03/11 10:50:29 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

/*void *ft_realloc(void *ptr, size_t new_size)
{
    // If new_size is 0, free memory and return NULL
    if (new_size == 0)
	{
        free(ptr);
        return NULL;
    }
    
    // If ptr is NULL, behave like malloc(new_size)
    if (ptr == NULL)
	{
        return malloc(new_size);
    }
    
    // Allocate new memory block
    void *new_ptr = malloc(new_size);
    if (!new_ptr)
	{
        return NULL; // Memory allocation failed
    }
    
    // Copy the old data to the new block (copy only the minimum size)
    size_t old_size = malloc_usable_size(ptr); // This function is platform-dependent
    memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
    
    free(ptr);
    
    return new_ptr;
}*/

char *ft_strndup(const char *s, size_t n)
{
    size_t len = 0;
    char *dup;

    while (s[len] && len < n)
        len++;

    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;

    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];

    dup[len] = '\0';

    return (dup);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

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