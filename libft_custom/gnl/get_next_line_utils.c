/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:06:26 by bboukach          #+#    #+#             */
/*   Updated: 2024/11/21 15:16:12 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	j = -1;
	i = -1;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (++i, s1[i])
		res[i] = s1[i];
	while (++j, s2[j])
		res[i++] = s2[j];
	res[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (res);
}

char	*ft_strchr_gnl(char *str, int c)
{
	size_t	i;
	char	cc;

	i = 0;
	cc = (char)c;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == cc)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == cc)
		return ((char *)&str[i]);
	return (NULL);
}
