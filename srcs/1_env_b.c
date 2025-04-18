/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_env_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:20:07 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/18 17:20:10 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*e;
	t_env	*new;
	char	**temp;

	i = 0;
	e = NULL;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if (!temp)
			return (NULL);
		new = env_new(ft_strdup(temp[0]), ft_strdup(temp[1]));
		env_addback(&e, new);
		free_doublechar(temp);
		i++;
	}
	return (e);
}
