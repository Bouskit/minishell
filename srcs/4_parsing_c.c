/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:37:45 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/28 19:43:48 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_token	*process_tokens_loop(t_command **cmd, t_command **first_cmd,
		t_token *tokens, t_index *num)
{
	t_token	*current;
	t_token	*next;
	t_token	*head;

	head = tokens;
	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == PIPE)
		{
			if (!handle_pipe(cmd, first_cmd, num))
				return (NULL);
		}
		else if (!handle_non_pipe(cmd, &current, num))
			return (NULL);
		current = next;
	}
	return (head);
}

static int	init_command(t_command **cmd, t_command **first_cmd, t_index *num)
{
	*cmd = new_command(0);
	if (!(*cmd))
		return (0);
	num->cmd_count = 1;
	*first_cmd = *cmd;
	return (1);
}

t_command	*parse_tokens(char *cmd_line, t_env *env, int exit_code)
{
	t_command	*cmd;
	t_command	*first_cmd;
	t_token		*tokens;
	t_index		num;

	tokens = init_parsing(cmd_line, env, exit_code, &num);
	if (!tokens)
		return (NULL);
	if (!init_command(&cmd, &first_cmd, &num))
	{
		free_tokens(tokens);
		return (NULL);
	}
	tokens = process_tokens_loop(&cmd, &first_cmd, tokens, &num);
	if (!tokens)
	{
		free_tokens(tokens);
		free_cmd(first_cmd);
		return (NULL);
	}
	free_tokens(tokens);
	return (first_cmd);
}
