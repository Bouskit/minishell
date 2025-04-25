/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:37:55 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/25 13:10:52 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	add_cmd_infile(t_command **cmd, t_token **token, int *in_i)
{
	size_t	old_in_size;

	old_in_size = 0;
	if (*in_i > 0)
		old_in_size = sizeof(int) * (*in_i + 1);
	(*cmd)->in = ft_realloc((*cmd)->in, old_in_size, sizeof(int) * (*in_i + 2));
	if (!(*cmd)->in)
		return (0);
	(*cmd)->in[*in_i] = ((*token)->type == HEREDOC);
	*token = (*token)->next;
	old_in_size = 0;
	if (*in_i > 0)
		old_in_size = sizeof(char *) * (*in_i + 1);
	(*cmd)->infile = ft_realloc((*cmd)->infile,
			old_in_size, sizeof(char *) * (*in_i + 2));
	if (!(*cmd)->infile)
		return (0);
	(*cmd)->infile[*in_i] = ft_strdup((*token)->value);
	if (!(*cmd)->infile[*in_i])
		return (0);
	(*cmd)->infile[++(*in_i)] = NULL;
	(*cmd)->in[*in_i] = -5;
	return (1);
}

int	add_cmd_outfile(t_command **cmd, t_token **token, int *out_i)
{
	size_t	old_append_size;
	size_t	old_outfile_size;

	old_append_size = 0;
	if (*out_i > 0)
		old_append_size = sizeof(int) * (*out_i + 1);
	(*cmd)->append = ft_realloc((*cmd)->append, old_append_size,
			sizeof(int) * (*out_i + 2));
	if (!(*cmd)->append)
		return (0);
	(*cmd)->append[*out_i] = ((*token)->type == APPEND);
	*token = (*token)->next;
	old_outfile_size = 0;
	if (*out_i > 0)
		old_outfile_size = sizeof(char *) * (*out_i + 1);
	(*cmd)->outfile = ft_realloc((*cmd)->outfile, old_outfile_size,
			sizeof(char *) * (*out_i + 2));
	if (!(*cmd)->outfile)
		return (0);
	(*cmd)->outfile[*out_i] = ft_strdup((*token)->value);
	if (!(*cmd)->outfile[*out_i])
		return (0);
	(*cmd)->outfile[++(*out_i)] = NULL;
	(*cmd)->append[*out_i] = -5;
	return (1);
}

t_token	*init_parsing(char *cmd_line, t_env *env, int exit_code, t_index *num)
{
	t_token	*token;
	t_token	*tokens;

	num->ac = 0;
	num->out_i = 0;
	num->in_i = 0;
	num->cmd_count = 0;
	token = tokenization(cmd_line);
	if (!token || !check_syntax(token))
	{
		free_tokens(token);
		return (NULL);
	}
	free (cmd_line);
	tokens = expand_tokens(token, env, exit_code);
	free_tokens(token);
	if (!tokens)
		return (NULL);
	return (tokens);
}

bool	handle_pipe(t_command **cmd, t_command **first_cmd, t_index *num)
{
	t_command	*new;

	new = new_command (num->cmd_count++);
	if (!add_command(first_cmd, new))
		return (false);
	*cmd = new;
	*num = (t_index){.cmd_count = num->cmd_count};
	return (true);
}

bool	handle_non_pipe(t_command **cmd, t_token **tokens,
		t_index *num)
{
	if ((*tokens)->type == WORD)
		return (add_cmd_args(cmd, tokens, &num->ac));
	else if ((*tokens)->type == R_IN || (*tokens)->type == HEREDOC)
		return (add_cmd_infile(cmd, tokens, &num->in_i));
	else if ((*tokens)->type == R_OUT || (*tokens)->type == APPEND)
		return (add_cmd_outfile(cmd, tokens, &num->out_i));
	return (true);
}
