/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:38:30 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/15 00:37:19 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	empty_line(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i] && ft_is_space(cmd_line[i]))
		i++;
	if (i == (int)ft_strlen(cmd_line))
	{
		free(cmd_line);
		return (1);
	}
	return (0);
}

int	check_syntax(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == PIPE)
	{
		ft_putstr_fd("Syntax error: Invalid command line near '|'.\n", 2);
		return (0);
	}
	while (token)
	{
		if ((token->type == PIPE || token->type == R_IN
				|| token->type == R_OUT || token->type == APPEND
				|| token->type == HEREDOC)
			&& (!token->next || token->next->type != WORD))
		{
			ft_putstr_fd("Syntax error:  Invalid command line \n", 2);
			return (0);
		}
		token = token->next;
	}
	return (1);
}

t_command	*new_command(int index)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->in = NULL;
	cmd->infile = NULL;
	cmd->append = NULL;
	cmd->outfile = NULL;
	cmd->index = index;
	cmd->next = NULL;
	return (cmd);
}

int	add_command(t_command **cmds, t_command *new)
{
	t_command	*tmp;

	if (!new || !cmds)
		return (0);
	if (!*cmds)
	{
		*cmds = new;
		return (1);
	}
	tmp = *cmds;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	return (1);
}

int	add_cmd_args(t_command **cmds, t_token **token, int *ac)
{
	size_t	old_size;

	old_size = 0;
	if (*ac > 0)
		old_size = sizeof(char *) * (*ac + 1);
	(*cmds)->args = ft_realloc((*cmds)->args,
			old_size, sizeof(char *) * (*ac + 2));
	if (!(*cmds)->args)
		return (0);
	(*cmds)->args[*ac] = ft_strdup((*token)->value);
	if (!(*cmds)->args[*ac])
		return (0);
	(*cmds)->args[++(*ac)] = NULL;
	return (1);
}
