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
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*tokens)
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
}

t_token_type	operator_type(char	*str)
{
	if (ft_strlen(str) == 2)
	{
		if ((!strncmp(str, ">>", 2))) return (APPEND);
		if ((!strncmp(str, "<<", 2))) return (HEREDOC);
	}
	if ((!strncmp(str, "|", 1))) return (PIPE);
	if ((!strncmp(str, ">", 1))) return (R_OUT);
	if ((!strncmp(str, "<", 1))) return (R_IN);
	fprintf(stderr, "Error: Unexpected input to get_operator_type: %s\n", str);
	return (ERROR_TOKEN);
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

	start = *i + 1;
	len = 0;
	while (cmd_line[*i] && cmd_line[*i] != half_quote)
	{
		(*i)++;
		len++;
	}
	if (cmd_line[*i] != half_quote)
		return (NULL);
	result = ft_substr(cmd_line, start, len);
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
			if ((cmd_line[i] == '>' || cmd_line[i] == '<') && cmd_line[i + 1] && cmd_line[i + 1] == cmd_line[i])
            {
                op[1] = cmd_line[i + 1];
				i++;
            }
			i++;
			add_token(&tokens, new_token(op, operator_type(op)));
			continue;
		}
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
		{
			if (cmd_line[i] == '\'')
				tokens->type == QUOTE_SINGLE;
			if (cmd_line[i] == '"')
				tokens->type == QUOTE_DOUBLE;
			quoted_str = extract_quoted_string(cmd_line, &i, cmd_line[i]);
			if (!quoted_str)
			{
				ft_putstr_fd("unclosed quote", 2);
				return (0);
			}
			add_token(&tokens, new_token(quoted_str, tokens->type));

		}
		else if(cmd_line[i] || cmd_line[i] != '\'' && cmd_line[i] != '"')
		{
			start = i;
			while (cmd_line[i] && !isspace(cmd_line[i]) && !is_operator(cmd_line[i]))
			{
				i++;
			}
			word = ft_strndup(&cmd_line[start], i - start);
			add_token(&tokens, new_token(word, WORD));
			free (word);
			continue;
		}
	}
	return (tokens);
}



int main()
{
    char input[] = "echo 'ls | < > fda";
    t_token *tokens = tokenization(input);
    
    while (tokens)
    {
        printf("Token: [%s] Type: [%d]\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
    return 0;
}
