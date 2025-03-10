/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:19:36 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/08 16:37:02 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void builtins_exit(char *input, t_status *status)
{
	char **args;
	int exit_code;

	args = ft_split(input, ' ');
	
	if (!args[1])
	{
		free_doublechar(args);
		exit(status->exit_code);
	}
	if (!str_is_num(args[1]))
	{
		write(2, "exit\nminishell: exit: ", 22);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		free_doublechar(args);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		free_doublechar(args);
		return ;
	}
	exit_code = ft_atoi(args[1]) % 256;
	free_doublechar(args);
	exit(exit_code);
}