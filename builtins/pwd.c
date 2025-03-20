/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:19:50 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/08 16:36:58 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void builtins_pwd(t_env *e)
{
	t_env *tmp;

	tmp = e;
	while(tmp->next && ft_strcmp("PWD", tmp->name))
	{
		tmp = tmp->next;
	}
	printf("%s\n", tmp->value);
	return ;
}