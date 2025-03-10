/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:18:23 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/08 16:37:11 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void echo_no_option(char *input)
{
	ft_putstr_fd(input, 1);
	write(1, "\n", 1);
}

void echo_option(char *input)
{
	int i = 2;

	while (input[i] && input[i] != ' ')
	{
		if (input[i] != 'n')
		{
			echo_no_option(input);
			return;
		}
		i++;
	}
	input = input + i;
	ft_putstr_fd(input, 1);
} 

void builtins_echo(char *input)
{
	if (*input == ' ')
		input++;
	if (input[0] == '-' && input[1] == 'n')
		echo_option(input);
	else 
		echo_no_option(input);
}