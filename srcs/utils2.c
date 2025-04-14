/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:07:55 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/15 01:17:46 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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

void ft_putstr3(char *a1, char *a2, char *a3, int fd)
{
	if (a1)
		ft_putstr_fd(a1, fd);
	if (a2)
		ft_putstr_fd(a2, fd);
	if (a3)
		ft_putstr_fd(a3, fd);
}

