/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:38:30 by xiazhang          #+#    #+#             */
/*   Updated: 2025/03/10 20:38:33 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	check_syntax(t_token *token)
{
	if (!token)
		return (0);
	while (token)
	{
		if ((token->type == PIPE || token->type == R_IN
			|| token->type == R_OUT ||token->type == APPEND) 
			&& (!token->next || token->next->type != WORD))
		{
			ft_putstr_fd("Syntax error: Incompleted command line.\n", 2);
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
	if(!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->rout.outfile = NULL;
	cmd->rout.append = NULL;
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

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmd;
	t_command	*first_cmd;
	int			ac;
	int			out_i;
	int			append_i;
	int			heredoc_i;
	int			cmd_count;

	ac = 0;
	out_i = 0;
	append_i = 0;
	heredoc_i = 0;
	cmd_count = 1;
	cmd = new_command(++cmd_count);
	first_cmd = cmd;
	while (tokens)
	{
		if(tokens->type == WORD || tokens->type == QUOTE_DOUBLE || tokens->type == QUOTE_SINGLE)
		{
			cmd->args = realloc(cmd->args, sizeof(char *) * (ac + 2));
			if (!cmd->args)
			{
				free_cmd(first_cmd);
				return(NULL);
			}
			cmd->args[ac] = ft_strdup(tokens->value);
			if (!cmd->args[ac])
			{
				free_cmd(first_cmd);
				return (NULL);
			}
			cmd->args[++ac] = NULL;
		}
		else if (tokens->type == R_IN)
		{
			tokens = tokens->next;
			if (tokens)
			{
				free(cmd->infile);
				cmd->infile = ft_strdup(tokens->value);
			}
			if (!cmd->infile)
			{
				free_cmd(first_cmd);
				return (NULL);
			}
		}
		else if (tokens->type == R_OUT || tokens->type == APPEND)
		{
			cmd->rout.append =realloc(cmd->rout.append, sizeof(int)* (append_i + 1));
			if(!cmd->rout.append)
			{
				free_cmd(first_cmd);
				return (NULL);                                                                                                               
			}
			cmd->rout.append[append_i++] =(tokens->type == APPEND);
			tokens = tokens->next;
			cmd->rout.outfile= realloc(cmd->rout.outfile, sizeof(char *) * (out_i + 2));
			if(!cmd->rout.outfile)
			{
				free_cmd(first_cmd);
				return (NULL);
			}
			cmd->rout.outfile[out_i] = ft_strdup(tokens->value);
			if (!cmd->rout.outfile[out_i])
			{
				free_cmd(first_cmd);
				return (NULL);
			}
			cmd->rout.outfile[++out_i] = NULL;
		}
		else if (tokens->type ==  HEREDOC)
		{
			tokens = tokens->next;
			if (tokens)
			{
				cmd->heredoc = realloc(cmd->heredoc, sizeof(char *) * (heredoc_i + 2));
				if (!cmd->heredoc)
				{
					free_cmd(first_cmd);
					return (NULL);
				}
				cmd->heredoc[heredoc_i] = ft_strdup(tokens->value);
				cmd->heredoc[++heredoc_i] = NULL;
			}
		}
		else if(tokens->type == PIPE)
		{
			cmd = new_command(cmd_count++);
			if (!add_command(&first_cmd, cmd))
			{
				free_cmd(first_cmd);
				return (NULL);
			}
			ac = 0;
			out_i = 0;
			append_i = 0;
			heredoc_i = 0;
			
		}
		tokens = tokens->next;
	}
	return (first_cmd);
}

