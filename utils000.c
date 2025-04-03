/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils000.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:07:55 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/02 17:34:25 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	strcmp_space(char *s1, char *s2)
{
	int	i;

	i = 0;
	while(s1[i] == ' ' || s1[i] == '\t')
		i++;
	while(s2[i] == ' ' || s2[i] == '\t')
		i++;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int str_is_num(char *str)
{
	if (*str == '-')
		str++;
	while(*str)
	{
		if(!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void free_doublechar(char **str)
{
	int i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

