/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:10:50 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/08 17:33:59 by bboukach         ###   ########.fr       */
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

void remove_space(char *input)
{
	int start = 0;
	int end = 0;
	int i = 0;

	while(input[start] == ' ' || input[start] == '\t')
		start++;
	end = start;
	while(input[end])
		end++;
	end--;
	while(input[end] == ' ' || input[end] == '\t')
		end--;
	while(start <= end)
	{
		input[i] = input[start];
		start++;
		i++;
	}
	input[i] = '\0';
}

void cmd_not_found(char *input)
{
	write(2, "minishell: ", 11);
	write(2, input, ft_strlen(input));
	write(2, ": command not found\n", 20);
}

void do_input(char *input, t_env *e, t_status *status)
{
	remove_space(input);
	if (ft_strcmp(input, "pwd") == 0)
		builtins_pwd(e);
	else if (ft_strcmp(input, "env") == 0)
		builtins_env(e);
	else if (ft_strncmp(input, "exit", 4) == 0 && (input[4] == ' ' || input[4] == '\0'))
		builtins_exit(input, status);
	else if (ft_strncmp(input, "echo", 4) == 0 && (input[4] == ' ' || input[4] == '\0'))
		builtins_echo(input + 4);
	else if (ft_strncmp(input, "export", 6) == 0 && (input[6] == ' ' || input[6] == '\0'))
		builtins_export(input + 6, e);
	else 
		cmd_not_found(input);
}