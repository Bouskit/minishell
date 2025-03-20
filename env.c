/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:45:52 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/20 23:53:35 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void free_env(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env;
        env = env->next;

        free(tmp->name);
        free(tmp->value);

        free(tmp);
    }
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

t_env	*env_last(t_env *e)
{
	t_env *tmp;
	
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

void env_addback(t_env **env, t_env *new)
{
	if (!env || !new)
		return;
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

t_env *init_env(char **envp)
{
	int i = 0;
	t_env *e = NULL;
	t_env *new;
	char **temp;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if(!temp)
			return (NULL);
		new = env_new(ft_strdup(temp[0]), ft_strdup(temp[1]));
		env_addback(&e, new);
		free_doublechar(temp);
		i++;
	}
	return (e);
}