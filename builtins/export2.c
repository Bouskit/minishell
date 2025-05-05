/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:54:36 by bboukach          #+#    #+#             */
/*   Updated: 2025/05/04 23:05:43 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	update_var(t_env *env, char *name, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = value;
			}
			free(name);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	new_var(char *args, t_env **e)
{
	t_env	*new;
	int		i;
	char	*value;
	char	*name;

	i = 0;
	value = NULL;
	if (ft_strchr(args, '='))
	{
		while (args[i] != '=')
			i++;
		name = ft_substr(args, 0, i);
		if (args[i] != '\0')
			value = ft_substr(args, i + 1, ft_strlen(args));
	}
	else
		name = ft_strdup(args);
	if (update_var(*e, name, value))
		return ;
	new = env_new(name, value);
	env_addback(e, new);
}

int	export_equal(char *args)
{
	int	i;

	i = 0;
	if (!args[0] || (!ft_isalpha(args[0]) && args[0] != '_'))
		return (0);
	while (args[i] && args[i] != '=')
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_print(t_env *e)
{
	t_env	*tmp;

	tmp = e;
	while (tmp)
	{
		if (tmp->value)
			printf("export %s=\"%s\"\n", tmp->name, tmp->value);
		else
			printf("export %s\n", tmp->name);
		tmp = tmp->next;
	}
	free_env(e);
	return ;
}
