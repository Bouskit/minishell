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
	if (token->type == PIPE || token->type == R_IN
			|| token->type == R_OUT || token->type == HEREDOC || token->type == APPEND)
	{
		ft_putstr_fd("Syntax error: Unexpected operator at the beginning.\n", 2);
		return (0);
	}
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
	cmd->outfile = NULL;
	cmd->append = 0;
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

	cmd = new_command();
	first_cmd = cmd;
	ac = 0;
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
			cmd->append = (tokens->type == APPEND);
			tokens = tokens->next;
			if (tokens)
				cmd->outfile = ft_strdup(tokens->value);
		}
		else if(tokens->type == PIPE)
		{
			add_command(&first_cmd, cmd);
			cmd = new_command();
		}
		tokens = tokens->next;
	}
	return (first_cmd);
}

