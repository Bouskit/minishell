/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:38:30 by xiazhang          #+#    #+#             */
/*   Updated: 2025/03/10 20:38:33 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	check_syntax(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == PIPE || token->type == R_IN
			|| token->type == R_OUT || token->type == HEREDOC || token->type == APPEND)
	{
		ft_putstr_fd("Syntax error: Unexpected operator at the beginning.\n", 2);
		return (0);
	}
	while (token)
	{
		if ((token->type == PIPE || token->type == R_IN
			|| token->type == R_OUT ||token->type == APPEND) 
			&& (!token->next || token->next->type != WORD))
		{
			ft_putstr_fd("Syntax error: Incompleted command line.\n", 2);
			return (0);
		}
		token = token->next;
	}
	return (1);
}

