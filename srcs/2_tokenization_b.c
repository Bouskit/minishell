/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenization_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:28:00 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/18 17:28:03 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_quoted_word(char *line, int *i, char quote)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i])
		(*i)++;
}

char	*extract_word(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !ft_is_space(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			skip_quoted_word(line, i, line[*i]);
		else
			(*i)++;
	}
	return (ft_strndup(&line[start], *i - start));
}

int	unclosed_quote(char	*cmd_line)
{
	int		i;
	char	half_quote;

	i = 0;
	while (cmd_line[i])
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

bool	handle_operator(const char *line, int *i, t_token **tokens)
{
	char	op[3];

	op[0] = line[*i];
	if ((line[*i] == '>' || line[*i] == '<') && line[*i + 1] == line[*i])
		op[1] = line[++(*i)];
	else
		op[1] = '\0';
	op[2] = '\0';
	(*i)++;
	return (add_token(tokens, new_token(op, operator_type(op))));
}

bool	handle_word(char *line, int *i, t_token **tokens)
{
	char	*word;
	t_token	*new;

	word = extract_word(line, i);
	new = new_token(word, WORD);
	free(word);
	if (!new)
		return (false);
	return (add_token(tokens, new));
}
