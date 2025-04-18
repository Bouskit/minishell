/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:22:06 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/17 14:09:56 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	update_var(t_env *env, char *name, char *value)
{
    t_env *tmp;

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
	return ;
}

void swap_export(t_env *loop)
{
	char *name;
	char *value;

	name = loop->name;
	loop->name = loop->next->name;
	loop->next->name = name;
	value = loop->value;
	loop->value = loop->next->value;
	loop->next->value = value;
}

t_env *copy_export(t_env *e)
{
	t_env	*copy;
	t_env *tmp;

	copy = NULL;
	tmp = e;
	while (tmp)
	{
		env_addback(&copy, env_new(tmp->name, tmp->value));
		tmp = tmp->next;
	}
	return (copy);
}

void	export_sort(t_env *e)
{
	t_env	*loop;
	t_env	*copy;
	int		swap;
	int		i;
	int		len;

	swap = 1;
	copy = copy_export(e);
	len = env_size(copy) + 1;
	while (swap && --len > 0)
	{
		swap = 0;
		i = -1;
		loop = copy;
		while (++i < len - 1)
		{
			if (loop->next && ft_strcmp(loop->name, loop->next->name) > 0)
			{
				swap_export(loop);
				swap = 1;
			}
			loop = loop->next;
		}
	}
	export_print(copy);
}

int	do_export(char **args, t_env **e)
{
	int	i;

	i = 1;
	if (!args[1])
		export_sort(*e);
	while (args[i])
	{
		if (args[i] && export_equal(args[i]))
			new_var(args[i], e);
		else
			printf("minishell: export: \'%s\': not a valid identifier\n",
				args[i]);
		i++;
	}
	return (0);
}
