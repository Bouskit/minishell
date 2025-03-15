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

t_command	*new_command(void)
{
	t_command	*cmd;
	cmd = malloc(sizeof(t_command));
	if(!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->rout.outfile = NULL;
	cmd->rout.append = NULL;
	cmd->index = 0;
	cmd->next = NULL;
	return (cmd);
}

void	add_command(t_command **cmds, t_command *new)
{
	t_command	*tmp;

	if (!*cmds)
	{
		*cmds = new;
		return ;
	}
	tmp = *cmds;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmd;
	t_command	*first_cmd;
	int			ac;
	int			out_i;
	int			append_i;

	cmd = new_command();
	first_cmd = cmd;
	ac = 0;
	out_i = 0;
	append_i = 0;
	while (tokens)
	{
		if(tokens->type == WORD || tokens->type == QUOTE_DOUBLE || tokens->type == QUOTE_SINGLE)
		{
			cmd->args = realloc(cmd->args, sizeof(char *) * (ac + 2));
			cmd->args[ac++] = ft_strdup(tokens->value);
			cmd->args[ac] = NULL;
		}
		else if (tokens->type == R_IN)
		{
			tokens = tokens->next;
			if (tokens)
				cmd->infile = ft_strdup(tokens->value);
		}
		else if (tokens->type == R_OUT || tokens->type == APPEND)
		{
			cmd->rout.append =realloc(cmd->rout.append, sizeof(int)* (append_i + 1));
			if(!cmd->rout.append)
			{
				free_all();
				return (NULL);
			}
			cmd->rout.append[append_i++] =(tokens->type == APPEND);
			tokens = tokens->next;
			//if (tokens)
			//{
			cmd->rout.outfile= realloc(cmd->rout.outfile, sizeof(char *) * (out_i + 2));
			if(!cmd->rout.outfile)
			{
				free_all();
				return (NULL);
			}
			cmd->rout.outfile[out_i++] = ft_strdup(tokens->value);
			cmd->rout.outfile[out_i] = NULL;
			//}
			/*else
			{
				free_all()
			}*/
		}
		else if(tokens->type == PIPE)
		{
			add_command(&first_cmd, cmd);
			cmd = new_command();
			cmd->index++;
		}
		tokens = tokens->next;
	}
	return (first_cmd);
}

