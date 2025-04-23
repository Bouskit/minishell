/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expand_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:29:00 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/18 21:29:03 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_dollar(t_expand *exp)
{
	exp->i++;
	if (exp->input[exp->i] == '?')
		append_exit_status(exp);
	else if (ft_isalpha(exp->input[exp->i]) || exp->input[exp->i] == '_')
		extract_var(exp);
	else if (exp->input[exp->i] == '\0' || exp->input[exp->i] == '\''
		|| exp->input[exp->i] == '"' || exp->input[exp->i] == ' ')
	{
		exp->result = append_char_safe(exp->result, '$');
		exp->i--;
	}
	else
	{
		exp->result = append_char_safe(exp->result, '$');
		exp->i--;
	}
	if (!exp->result && exp->status == 0)
		exp->status = 1;
}

void	char_none(t_expand *exp)
{
	char	current_char;

	current_char = exp->input[exp->i];
	if (current_char == '\'')
		exp->state = SQUOTE;
	else if (current_char == '"')
		exp->state = DQUOTE;
	else if (current_char == '$')
		handle_dollar(exp);
	else
	{
		exp->result = append_char_safe(exp->result, current_char);
		if (!exp->result)
			exp->status = 1;
	}
}

void	char_squotes(t_expand *exp)
{
	char	current_char;

	current_char = exp->input[exp->i];
	if (current_char == '\'')
		exp->state = NONE;
	else
	{
		exp->result = append_char_safe(exp->result, current_char);
		if (!exp->result)
			exp->status = 1;
	}
}

void	char_dquotes(t_expand *exp)
{
	char	current_char;

	current_char = exp->input[exp->i];
	if (current_char == '"')
		exp->state = NONE;
	else if (current_char == '$')
		handle_dollar(exp);
	else
	{
		exp->result = append_char_safe(exp->result, current_char);
		if (!exp->result)
			exp->status = 1;
	}
}

void	init_expand(t_expand *exp, char *input, t_env *env, int exit_code)
{
	exp->input = input;
	exp->env = env;
	exp->exit_code = exit_code;
	exp->result = NULL;
	exp->i = 0;
	exp->state = NONE;
	exp->status = 0;
}
