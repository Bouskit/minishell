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
		if (!env_append(&env, envp[i]))
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
	if (!env_append(&env, ft_strdup("OLDPATH=")))
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
			env_append(&env, pwd);
		}
	}
	return (env);
}

void free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*start;

	start = env;
	if (!env)
		return;
	while (env->var)
	{
		tmp = env->next;
		free (env->var);
		free (env);
		env = tmp;
		if (env == start)
			break;
	}
}

t_env	*env_new_ele(char *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = ft_strdup(env);
	if (!new->var)
	{
		free(new);
		return (NULL);
	}
	new->prev = new;
	new->next = new;
	return (new);
}

int	env_append(t_env **env, char *var)
{
	t_env	*new;
	t_env	*tail;
	new = env_new_ele(var);
	if (!new)
		return (0);
	if (!(*env))
		*env = new;
	else
	{
		tail = (*env)->prev;
		tail->next = new;
		new->prev = tail;
		new->next = *env;
		(*env)->prev = new;
	}
	return (1);
}

void	print_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	tmp = env;
	printf ("%s", env->var);
	tmp = tmp->next;
	while (tmp != env)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}

}

