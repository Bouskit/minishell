/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:20:21 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/13 13:25:02 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free_tokens(new);
		return (NULL);
	}
	new->type = type;
	return (new);
}

int	add_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!new || !tokens)
		return (0);
	if (!(*tokens))
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	return (1);
}

t_token_type	operator_type(char	*str)
{
	if (ft_strlen(str) == 2)
	{
		if ((!ft_strncmp(str, ">>", 2)))
			return (APPEND);
		if ((!ft_strncmp(str, "<<", 2)))
			return (HEREDOC);
	}
	if ((!ft_strncmp(str, "|", 1)))
		return (PIPE);
	if ((!ft_strncmp(str, ">", 1)))
		return (R_OUT);
	if ((!ft_strncmp(str, "<", 1)))
		return (R_IN);
	ft_putstr_fd("Error: Unexpected input to get_operator_type", 2);
	return (ERROR);
}

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
	|| c == '\v');
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}
