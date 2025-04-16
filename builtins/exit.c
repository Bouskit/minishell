/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:19:36 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/15 01:22:02 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	do_exit(char **args)
{
	int	exit_code;

	if (!args[1])
		exit(0);
	if (!str_is_num(args[1]))
	{
		write(2, "exit\nminishell: exit: ", 22);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(args[1]) % 256;
	exit(exit_code);
	return (0);
}
