/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:06:04 by bboukach          #+#    #+#             */
/*   Updated: 2025/01/26 21:00:58 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

char	*stock_words(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	len;

	len = end - start;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_memcpy(word, &s[start], len);
	word[len] = '\0';
	return (word);
}

static void	*ft_free(char **str, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	**boucle(char **res, char const *s, char c)
{
	size_t	i;
	size_t	z;
	size_t	start;
	size_t	end;

	i = 0;
	z = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		end = i;
		if (end > start)
		{
			res[z] = stock_words(s, start, end);
			if (!(res[z]))
				return (ft_free(res, z));
			z++;
		}
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!res)
		return (NULL);
	return (boucle(res, s, c));
}
/*int main(void)
{
	char *input = "Hello, World!, fdp,  ";
	char delimiter = ',';

	char **result = ft_split(input, delimiter);

	printf("Original string: %s\n", input);
	printf("Splitted words:\n");

	int i = 0;
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	for (i = 0; result[i]; i++)
		free(result[i]);
	free(result);

	return (0);
}*/
