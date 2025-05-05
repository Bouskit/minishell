/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:37:45 by xiazhang          #+#    #+#             */
/*   Updated: 2025/05/04 23:08:09 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*parse_tokens(char *cmd_line, t_env *env, int exit_code)
{
	t_command	*cmd;
	t_command	*first_cmd;
	t_token		*tokens;
	t_index		num;
	t_token		*tofree;

	tokens = init_parsing(cmd_line, env, exit_code, &num);
	cmd = new_command(0);
	if (!tokens || !cmd)
		return (free_tokens(tokens), free_cmd(cmd), NULL);
	num.cmd_count = 1;
	first_cmd = cmd;
	tofree = tokens;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (!handle_pipe(&cmd, &first_cmd, &num))
				return (free_tokens(tokens), free_cmd(first_cmd), NULL);
		}
		else if (!handle_non_pipe(&cmd, &tokens, &num))
			return (free_tokens(tokens), free_cmd(first_cmd), NULL);
		tokens = tokens->next;
	}
	free_tokens(tofree);
	return (first_cmd);
}
