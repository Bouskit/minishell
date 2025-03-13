/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:22:06 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/13 15:37:29 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void new_var(char *args, t_env **e)
{
	t_env *tmp;
	t_env *new;
	int i = 0;
	char *value;

	tmp = *e;
	while (args[i] != '=')
		i++;
	value = ft_strdup(args + i + 1);
	new = env_new(ft_substr(args, 0, i), value);
	env_addback(e, new);
}

int export_equal(char *args)
{
    int i = 0;
    
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

void export_print(t_env *e)
{
	t_env *tmp;

	tmp = e;
	while(tmp->next)
	{
		printf("export %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	printf("export %s=\"%s\"\n", tmp->name, tmp->value);
	return ;
}

void export_sort(t_env **e)
{
	t_env *loop;
	char *tmp;
	int swap = 1;
	int i;
	int len = env_size(*e);

	while(swap)
	{
		swap = 0;
		i = 0;
		loop = *e;
		while (i < len - 1)
		{
			if (loop->next && ft_strcmp(loop->name, loop->next->name) > 0)
			{
				tmp = loop->name;
				loop->name = loop->next->name;
				loop->next->name = tmp;

				tmp = loop->value;
				loop->value = loop->next->value;
				loop->next->value = tmp;
				
				swap = 1;
			}
			loop = loop->next;
			i++;
		}
		len--;
	}
	export_print(*e);
}

void builtins_export(char **args, t_env *e)
{
	int i = 1;
	if (!args[1])
		export_sort(&e);
	while (args[i])
	{
		if (args[i] && export_equal(args[i]))
			new_var(args[i], &e);
		else 
			printf("minishell: export: \'%s\': not a valid identifier\n", args[i]);
		i++;
	}
	return;
}