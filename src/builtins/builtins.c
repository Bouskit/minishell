/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:10:50 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/11 14:09:28 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
echo with option -n
cd with only a relative or absolute path
//    pwd with no options
export with no options
unset with no options
//    env with no options or arguments
//    exit with no options
*/

void cmd_not_found(char *input)
{
	write(2, "minishell: ", 11);
	write(2, input, ft_strlen(input));
	write(2, ": command not found\n", 20);
}

void do_input(char *input, t_env *e, t_status *status)
{
	char **args;

	args = ft_split(input, ' ');
	if (ft_strcmp(args[0], "pwd") == 0)
		builtins_pwd(e);
	else if (ft_strcmp(args[0], "env") == 0 && !args[1])
		builtins_env(e);
	else if (ft_strcmp(args[0], "exit") == 0)
		builtins_exit(args, status);
	else if (ft_strcmp(args[0], "echo") == 0)
		builtins_echo(args);
	else if (ft_strcmp(args[0], "export") == 0)
		builtins_export(args, e);
	else 
		cmd_not_found(input);
	free_doublechar(args);
}