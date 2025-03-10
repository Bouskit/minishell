/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:24:15 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/08 17:29:18 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	env_size(t_env *lst)
{
	t_env	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

