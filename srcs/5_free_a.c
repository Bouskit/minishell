/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_free_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:57:39 by xiazhang          #+#    #+#             */
/*   Updated: 2025/05/04 15:01:57 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_cmd_args(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->in)
		free(cmd->in);
}

static void	free_cmd_infiles(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->infile)
	{
		while (cmd->infile[i])
			free(cmd->infile[i++]);
		free(cmd->infile);
	}
}

static void	free_cmd_outfiles(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->append)
		free(cmd->append);
	if (cmd->outfile)
	{
		while (cmd->outfile[i])
			free(cmd->outfile[i++]);
		free(cmd->outfile);
	}
}

void	free_cmd(t_command *cmds)
{
	t_command	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_cmd_args(tmp);
		free_cmd_infiles(tmp);
		free_cmd_outfiles(tmp);
		free(tmp);
	}
}
