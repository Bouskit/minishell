/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:22:06 by bboukach          #+#    #+#             */
/*   Updated: 2025/05/04 23:05:38 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_export(t_env *loop)
{
	char	*name;
	char	*value;

	name = loop->name;
	loop->name = loop->next->name;
	loop->next->name = name;
	value = loop->value;
	loop->value = loop->next->value;
	loop->next->value = value;
}

t_env	*copy_export(t_env *e)
{
	t_env	*copy;
	t_env	*tmp;

	copy = NULL;
	tmp = e;
	while (tmp)
	{
		env_addback(&copy, env_new(ft_strdup(tmp->name),
				ft_strdup(tmp->value)));
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
	free_env(copy);
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
