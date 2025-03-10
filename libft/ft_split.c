/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:34:04 by xiazhang          #+#    #+#             */
/*   Updated: 2024/10/30 18:34:06 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

int	word_count(char const *s, char c)//word_count 
{
	int	flag;
	int	count;

	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			flag = 0;
		else if (*s != c && !flag)
		{
			count++;
			flag = 1;
		}
		s++;
	}
	return (count);
}

char	*write_word(const char *s, char c)//write word chunk 
{
	int			len_chunk;
	const char	*start;
	char		*word_chunk;
	int			i_chunk;

	len_chunk = 0;
	start = s;
	while (s[len_chunk] && s[len_chunk] != c)
		len_chunk++;
	word_chunk = (char *)malloc((len_chunk + 1) * sizeof(char));
	if (!word_chunk)
		return (NULL);
	i_chunk = 0;
	while (i_chunk < len_chunk)
	{
		word_chunk[i_chunk] = s[i_chunk];
		i_chunk++;
	}
	word_chunk[i_chunk] = '\0';
	return (word_chunk);
}

char	**ft_split(char const *s, char c)//split
{
	char	**result;
	int		i_pointer;
	int		word_counter;

	word_counter = word_count(s, c);
	result = (char **)malloc((word_counter + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	i_pointer = 0;
	while (i_pointer < word_counter && *s)
	{
		while (*s == c)
			s++;
		result[i_pointer] = write_word(s, c);
		if (!result[i_pointer])
		{
			while (i_pointer >= 0)
				free(result[i_pointer--]);
			free(result);
			return (NULL);
		}
		s += ft_strlen(result[i_pointer++]);
	}
	result[word_counter] = NULL;
	return (result);
}
