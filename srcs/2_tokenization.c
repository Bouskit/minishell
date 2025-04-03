/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:20:21 by xiazhang          #+#    #+#             */
/*   Updated: 2025/03/09 17:20:23 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if(!new)
		return (NULL);
	new->next = NULL;
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free_tokens(new);
		return (NULL);
	}
	new->type = type;
	if (new->type == ERROR)
	{
		free_tokens(new);
		return (NULL);
	}
	return (new);
}

int	add_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!new || !tokens)
		return (0) ;
	if (!(*tokens))
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
		{
			tmp = tmp->next;
			//printf("add token\n");
		}
		tmp->next = new;
	}
	return (1);
}

t_token_type	operator_type(char	*str)
{
	if (ft_strlen(str) == 2)
	{
		if ((!ft_strncmp(str, ">>", 2))) return (APPEND);
		if ((!ft_strncmp(str, "<<", 2))) return (HEREDOC);
	}
	if ((!ft_strncmp(str, "|", 1))) return (PIPE);
	if ((!ft_strncmp(str, ">", 1))) return (R_OUT);
	if ((!ft_strncmp(str, "<", 1))) return (R_IN);
	fprintf(stderr, "Error: Unexpected input to get_operator_type: %s\n", str);
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
static char	*extract_quoted_string(char *cmd_line, int *i, char half_quote)
{
	int		start;
	char	*result;
	int		len;

	start = ++(*i);
	len = 0;
	while (cmd_line[*i] && cmd_line[*i] != half_quote)
	{
		(*i)++;
		len++;
	}
	if (cmd_line[*i] != half_quote)
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		return (NULL);
	}
	result = ft_substr(cmd_line, start, len);
	if (!result)
	{	
		ft_putstr_fd("Error: Failed to malloc\n", 2);
		return (NULL);
	}
	return (result);
}
t_token	*tokenization(char *cmd_line)
{
	t_token	*tokens;
	int		i;
	char	op[3] = {0};
	int		start;
	char	*word;
	char	*quoted_str;

	tokens =  NULL;
	i = 0;
	while (cmd_line[i])
	{
		if (ft_is_space(cmd_line[i]))
		{
			i++;
			continue;
		}
		if (is_operator(cmd_line[i]))
		{
			op[0] = cmd_line[i];
			if ((cmd_line[i] == '>' || cmd_line[i] == '<') && cmd_line[i + 1] == cmd_line[i])
            {
                op[1] = cmd_line[i + 1];
				op[2] = '\0';
				i++;
            }
			else
				op[1] = '\0';
			i++;
			if(!add_token(&tokens, new_token(op, operator_type(op))))
			{
				
				free_tokens(tokens);
				return (NULL);
			}
			continue;
		}
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
		{
			char current_quote;
			current_quote = cmd_line[i];
			quoted_str = extract_quoted_string(cmd_line, &i, current_quote);
			if (!quoted_str)
			{
				free_tokens(tokens);
				return (0);
			}
			if (current_quote == '\'')
			{
				if(!add_token(&tokens, new_token(quoted_str, QUOTE_SINGLE)))
				{
					free_tokens(tokens);
					return (NULL);
				}
			}
			if (current_quote == '"')
			{	
				if(!add_token(&tokens, new_token(quoted_str, QUOTE_DOUBLE)))
				{
					free_tokens(tokens);
					return (NULL);
				}
			}
			free (quoted_str);
			i++;
			continue;
		}
		else
		{
			start = i;
			while (cmd_line[i] && !isspace(cmd_line[i]) && !is_operator(cmd_line[i]))
			{
				i++;
			}
			word = ft_strndup(&cmd_line[start], i - start);
			if (!add_token(&tokens, new_token(word, WORD)))
			{
				free_tokens(tokens);
				return (NULL);
			}
			free (word);
			continue;
		}
	}
	return (tokens);
}

