/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:19:57 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/14 21:14:01 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void builtins_env(t_env *e)
{
	t_env *tmp;

	tmp = e;
	while(tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		else 
			printf("%s=\n", tmp->name);
		tmp = tmp->next;
	}
	return ;
}