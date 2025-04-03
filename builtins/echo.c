/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:18:23 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/03 00:57:44 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void echo_no_option(char **args)
{
	int i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return ;
}

void echo_option(char **args)
{
	int i = 2;

	while (args[1][i] && args[1][i] != ' ')
	{
		if (args[1][i] != 'n')
		{
			echo_no_option(args);
			return;
		}
		i++;
	}
	i = 2;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	return ;
} 

int do_echo(char **args)
{
	if (args[1] && args[1][0] == '-' && args[1][1] == 'n')
		echo_option(args);
	else 
		echo_no_option(args);
	return (0);
}