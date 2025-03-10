/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:19:57 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/08 17:42:01 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void builtins_env(t_env *e)
{
	t_env *tmp;

	tmp = e;
	while(tmp->next)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	printf("%s=%s\n", tmp->name, tmp->value);
	return ;
}