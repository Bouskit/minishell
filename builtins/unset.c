/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:55:04 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/03 00:41:35 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void unset_var(char *args, t_env **e)
{
	t_env *current;
	t_env *previous;

	if (!ft_strcmp(args, (*e)->name))
	{
		current = *e;
		*e = (*e)->next;
		free(current->name);
		if (current->value)
			free(current->value);
		free(current);
		return;
	}
	previous = *e;
	current = (*e)->next;
	while (current)
	{
		if (!ft_strcmp(args, current->name))
		{
			previous->next = current->next;
			free(current->name);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int do_unset(char **args, t_env **e)
{
	int i;

	i = 1;
	while(args[i])
	{
		unset_var(args[i], e);
		i++;
	}
	return (0);
}