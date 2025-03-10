/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:22:06 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/08 17:41:51 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void export_print(t_env *e)
{
	t_env *tmp;

	tmp = e;
	while(tmp->next)
	{
		printf("export %s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	printf("export %s=%s\n", tmp->name, tmp->value);
	return ;
}

void export_sort(t_env *e)
{
	t_env *loop;
	char *tmp;
	int swap = 1;
	int i;
	int len = env_size(e);

	while(swap)
	{
		swap = 0;
		i = 0;
		loop = e;
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
	export_print(loop);
}

void builtins_export(char *input, t_env *e)
{
	if (*input == '\0')
		export_sort(e);
	return;
}