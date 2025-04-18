/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expand_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:27:23 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/18 21:27:24 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*finalize_expand(t_expand *exp)
{
	if (exp->status != 0)
	{
		free(exp->result);
		return (NULL);
	}
	if (exp->result == NULL)
		return (ft_strdup(""));
	return (exp->result);
}

char	*expand_word(char *input, t_env *env, int exit_code)
{
	t_expand	exp;

	init_expand(&exp, input, env, exit_code);
	while (exp.input && exp.input[exp.i] && exp.status == 0)
	{
		if (exp.state == SQUOTE)
			char_squotes(&exp);
		else if (exp.state == DQUOTE)
			char_dquotes(&exp);
		else
			char_none(&exp);
		exp.i++;
	}
	return (finalize_expand(&exp));
}

int	word_token(t_token **expanded, t_token *current, t_env *env, int exit_code)
{
	char	*expanded_value;
	t_token	*new;

	expanded_value = expand_word(current->value, env, exit_code);
	if (!expanded_value)
		return (1);
	if (expanded_value[0] != '\0')
	{
		new = new_token(expanded_value, WORD);
		if (!new)
		{
			free(expanded_value);
			return (1);
		}
		if (!add_token(expanded, new))
		{
			free(expanded_value);
			free_tokens(new);
			return (1);
		}
	}
	free(expanded_value);
	return (0);
}

int	non_word_token(t_token **expanded, t_token *current)
{
	t_token	*new;

	new = new_token(current->value, current->type);
	if (!new)
		return (1);
	if (!add_token(expanded, new))
	{
		free_tokens(new);
		return (1);
	}
	return (0);
}

t_token	*expand_tokens(t_token *token_list, t_env *env, int exit_code)
{
	t_token	*expanded;
	t_token	*current;
	int		error_flag;

	expanded = NULL;
	current = token_list;
	error_flag = 0;
	while (current && error_flag == 0)
	{
		if (current->type == WORD)
			error_flag = word_token(&expanded, current, env, exit_code);
		else
			error_flag = non_word_token(&expanded, current);
		current = current->next;
	}
	if (error_flag != 0)
	{
		free_tokens(expanded);
		return (NULL);
	}
	return (expanded);
}
