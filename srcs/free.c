/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:57:39 by xiazhang          #+#    #+#             */
/*   Updated: 2025/03/11 12:57:41 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->name)
			free (tmp->name);
		if (tmp->value)
			free (tmp->value);
		free(tmp);
		env = tmp;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;
	
	if (!tokens)
		return;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free (tmp->value);
		free (tmp);
	}
}

void	free_cmd(t_command *cmds)
{
	t_command	*tmp;
	int	i;

	i = 0;
	while (cmds)
	{
		tmp =  cmds;
		cmds = cmds->next;
		while (tmp->args[i++])
		{
			free(tmp->args[i]);
		}
		if (tmp->infile)
			free (tmp->infile)
		if (tmp->outifle)
			free (tmp->outfile);

	}
}
