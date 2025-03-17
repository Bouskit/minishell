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
		if (tmp->value)
			free (tmp->value);
		free (tmp);
	}
}

void	free_cmd(t_command *cmds)
{
	t_command	*tmp;
	int	i;

	while (cmds)
	{
		tmp =  cmds;
		cmds = cmds->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free (tmp->args);//free tmp->args lists
		}
		if (tmp->infile)
			free (tmp->infile);// free infile pointer
		if (tmp->rout.append)
			free (tmp->rout.append);
		if (tmp->rout.outfile)
		{
			i = 0;
			while (tmp->rout.outfile[i])
				free(tmp->rout.outfile[i++]);
			free (tmp->rout.outfile);//free rout.outfile lists
		}
		if (tmp->heredoc)
		{
			i = 0;
			while (tmp->heredoc[i++])
				free(tmp->heredoc[i]);
			free (tmp->heredoc);//free heredoc lists
		}
		free(tmp);
	}
}
