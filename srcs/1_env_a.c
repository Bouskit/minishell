/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:52:34 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/14 15:38:19 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

t_env	*env_last(t_env *e)
{
	t_env	*tmp;

	if (!e)
		return (NULL);
	tmp = e;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_env	*env_new(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_addback(t_env **env, t_env *new)
{
	if (!env || !new)
		return ;
	if (*env)
		env_last(*env)->next = new;
	else
		*env = new;
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

void	increment_shlvl(t_env **env)
{
	t_env	*tmp;
	int		level;
	int		found;

	tmp = *env;
	found = 0;
	level = 0;
	while (tmp)
	{
		if (!ft_strcmp("SHLVL", tmp->name))
		{
			found = 1;
			if (tmp->value)
			{
				level = ft_atoi(tmp->value);
				free(tmp->value);
			}
			level++;
			tmp->value = ft_itoa(level);
		}
		tmp = tmp->next;
	}
	if (!found)
		env_addback(env, env_new(ft_strdup("SHLVL"), ft_strdup("1")));
}
