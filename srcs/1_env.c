/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:52:34 by xiazhang          #+#    #+#             */
/*   Updated: 2025/03/06 13:52:37 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

t_env	*env_new_ele(char *env)
{
	t_env	*new;
	int		i;
	int		start;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	while (env[i] && env[i] != '=')
		i++;
	new->name = ft_substr(env, 0, i);
	if (!new->name)
	{
		free_env(new);
		return (NULL);
	}
	i++;
	start = i;
	while (env[i])
		i++;
	new->value = ft_substr(env, start, i);
	if (!new->value)
	{
		free_env(new);
		return (NULL);
	}	
	return (new);
}

int	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return (0);
	if (!(*env))
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

t_env *init_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	if (!envp || !envp[0])
	{
		return (init_default_env());
	}
	while (envp[i])
	{
		if (!add_env(&env, env_new_ele (envp[i])))
		{
			free_env(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}

t_env *init_default_env()
{
	t_env	*env;
	char	path[PATH_MAX];
	char	*pwd;

	env = NULL;
	if (!add_env(&env, env_new_ele(ft_strdup("OLDPATH="))))
	{
		free_env(env);
		return (NULL);
	}
	if (getcwd(path, PATH_MAX))
	{
		pwd = malloc (5 + ft_strlen(path));
		if (pwd)
		{
			ft_strcpy(pwd, "PWD=");
			ft_strcat(pwd, path);
			add_env(&env, env_new_ele(pwd));
		}
	}
	return (env);
}




