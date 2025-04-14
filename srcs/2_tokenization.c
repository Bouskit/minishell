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


char	*extract_word(char *cmd_line, int *i) // 
{
	int	start;
	char	half_quote;

	start = *i;
	while(cmd_line[*i] && cmd_line[*i] != ' ' && cmd_line[*i] != '\n' && cmd_line[*i] != '\t' && cmd_line[*i] != '\v' && cmd_line[*i] != '\r' && cmd_line[*i] != '\f')
	{
		if (cmd_line[*i] == '\'' || cmd_line[*i] == '"')
		{
			half_quote = cmd_line[*i];
			(*i)++;
			while (cmd_line[*i] != half_quote)
				(*i)++;
			if (cmd_line[*i + 1] == '\0' || cmd_line[*i + 1] == ' ' || cmd_line[*i + 1] == '\n' || cmd_line[*i + 1] == '\r' || cmd_line[*i + 1] == '\f' || cmd_line[*i + 1] == '\t'  || cmd_line[*i + 1] == '\v')
			{
					(*i)++;
					return (ft_strndup(&cmd_line[start], *i - start));
			}
			else
				(*i)++;
		}
		else
			(*i)++;
	}
	return (ft_strndup(&cmd_line[start], *i - start));	
}

int	unclosed_quote(char	*cmd_line)
{
	int	i;
	char	half_quote;

	i = 0;
	while (cmd_line[i] )
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
		{
			half_quote = cmd_line[i];
			i++;
			while (cmd_line[i] && cmd_line[i] != half_quote)
				i++;
			if (cmd_line[i] != half_quote)
				return (1);
		}
		i++;
	}
	return (0);
}

t_token	*tokenization(char *cmd_line)
{
	t_token	*tokens;
	int		i;
	char	op[3] = {0};

	char	*word;
	if(unclosed_quote(cmd_line))
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		return (NULL);//check more carefully later the return value
	}
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
		else
		{
			word = extract_word(cmd_line, &i);
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



