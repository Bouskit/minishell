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
	if (token->type == PIPE)
	{
		ft_putstr_fd("Syntax error: Invalid command line near '|'.\n", 2);
		return (0);
	}
	while (token)
	{
		if ((token->type == PIPE || token->type == R_IN
			|| token->type == R_OUT ||token->type == APPEND || 
			token->type == HEREDOC) 
			&& (!token->next ||token->next->type != WORD))
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
	if(!cmd)
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

int add_cmd_args(t_command **cmds, t_token **token, int *ac)
{
	(*cmds)->args = realloc((*cmds)->args, sizeof(char *) * (*ac + 2));
	if (!(*cmds)->args)
		return (0);
	(*cmds)->args[*ac] = ft_strdup((*token)->value);
	if (!(*cmds)->args[*ac])
		return (0);
	(*cmds)->args[++(*ac)] = NULL;
	return (1);
}
int	add_cmd_outfile(t_command **cmd, t_token **token, int *out_i)
{
	(*cmd)->append = realloc((*cmd)->append, sizeof(int) * (*out_i + 2));
	if (!(*cmd)->append)
		return (0);
	(*cmd)->append[*out_i] = ((*token)->type == APPEND);
	*token = (*token)->next;
	(*cmd)->outfile = realloc((*cmd)->outfile, sizeof(char *) * (*out_i + 2));
	if (!(*cmd)->outfile)
		return (0);
	(*cmd)->outfile[*out_i] = ft_strdup((*token)->value);
	if (!(*cmd)->outfile[*out_i])
		return (0);
	(*cmd)->outfile[++(*out_i)] = NULL;
	(*cmd)->append[*out_i] = -5;
	return (1);
}
int	add_cmd_infile(t_command **cmd, t_token **token, int *in_i)
{
	(*cmd)->in = realloc((*cmd)->in, sizeof(int) * (*in_i + 2));
	if (!(*cmd)->in)
		return (0);
	(*cmd)->in[*in_i] = ((*token)->type == HEREDOC);
	*token = (*token)->next;
	(*cmd)->infile = realloc((*cmd)->infile, sizeof(char *) * (*in_i + 2));
	if (!(*cmd)->infile)
		return (0);
	(*cmd)->infile[*in_i] = ft_strdup((*token)->value);
	if (!(*cmd)->infile[*in_i])
		return (0);
	(*cmd)->infile[++(*in_i)] = NULL;
	(*cmd)->in[(*in_i)] = -5;
	return (1);
}
t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmd;
	t_command	*first_cmd;
	int			ac;
	int			out_i;
	int 		in_i;
	int			cmd_count;

	ac = 0;
	out_i = 0;
	in_i = 0;
	cmd_count = 0;
	

	cmd = new_command(cmd_count++);
	if (!cmd)
		return (NULL);
	first_cmd = cmd;
	
	while (tokens)
	{
		if(tokens->type == WORD || tokens->type == QUOTE_DOUBLE || tokens->type == QUOTE_SINGLE)
		{
			if (!add_cmd_args(&cmd, &tokens, &ac))
			{
				free_cmd(first_cmd);
				printf("Error: Failed to add command arguments\n");
				return (NULL);
			}
		}
		else if (tokens->type == R_IN || tokens->type == HEREDOC)
		{
			if (!add_cmd_infile(&cmd, &tokens, &in_i))
			{
				free_cmd(first_cmd);
				printf("Error: Failed to add command infile\n");
				return (NULL);
			}
		}
		else if (tokens->type == R_OUT || tokens->type == APPEND)
		{
			if (!add_cmd_outfile(&cmd, &tokens, &out_i))
			{
				free_cmd(first_cmd);
				printf("Error: Failed to add command outfile\n");
				return (NULL);
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
			in_i = 0;
			cmd->append = NULL;
			cmd->in = NULL;
		}
		tokens = tokens->next;
	}
	return (first_cmd);
}

