/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenization_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:33:08 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/18 17:33:11 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*tokenization(char *cmd_line)
{
	t_token	*tokens;
	int		i;

	if (unclosed_quote(cmd_line))
		return (ft_putstr_fd("Error: unclosed quote\n", 2), NULL);
	tokens = NULL;
	i = 0;
	while (cmd_line[i])
	{
		if (ft_is_space(cmd_line[i]))
			i++;
		if (is_operator(cmd_line[i]))
		{
			if (!handle_operator(cmd_line, &i, &tokens))
				return (free_tokens(tokens), NULL);
		}
		else if (!handle_word(cmd_line, &i, &tokens))
			return (free_tokens(tokens), NULL);
	}
	return (tokens);
}
