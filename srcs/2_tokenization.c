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

void	add_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*token)
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
		{
			tmp = tmp->next;
			printf("add token");
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

char *ft_strndup(const char *s, size_t n)
{
    size_t len = 0;
    char *dup;

    // Find the actual length to copy (min between string length and n)
    while (s[len] && len < n)
        len++;

    // Allocate memory (+1 for null terminator)
    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;

    // Copy the characters
    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];

    // Null-terminate the string
    dup[len] = '\0';

    return (dup);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	number;
	char	*ptr;
	char	*copy_ptr;

	number = ft_strlen(s);
	ptr = (char *)malloc((number + 1) * sizeof(char));
	copy_ptr = ptr;
	if (!ptr)
		return (NULL);
	while (*s)
	{
		*copy_ptr = *s;
		copy_ptr++;
		s++;
	}
	*copy_ptr = '\0';
	return (ptr);
}

t_token	*tokenization(char *cmd_line)
{
	t_token	*token;
	int		i;
	char	op[3] = {0};
	int		start;
	char	*word;

	token =  NULL;
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
			add_token(&token, new_token(op, operator_type(op)));
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
			add_token(&token, new_token(word, WORD));
			free (word);
			continue;
		}
	}
	return (token);
}



int main()
{
    char input[] = "echo ls | < > fda";
    t_token *tokens = tokenization(input);
    
    while (tokens)
    {
        printf("Token: [%s] Type: [%d]\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
    return 0;
}
