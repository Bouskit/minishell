/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:10:50 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/03 00:37:44 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtin(char *name)
{
	if (!ft_strcmp("echo", name) || !ft_strcmp("cd", name) \
	|| !ft_strcmp("pwd", name) || !ft_strcmp("export", name) \
	|| !ft_strcmp("unset", name) || !ft_strcmp("env", name) \
	|| !ft_strcmp("exit", name))
		return (1);
	else 
		return (0); 
}

int execute_builtin(t_command *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (do_echo(cmd->args));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (do_pwd());
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (do_exit(cmd->args));
	else if (!ft_strcmp(cmd->args[0], "env") && !cmd->args[1])
		return (do_env(env));	
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (do_export(cmd->args, &env));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (do_unset(cmd->args, &env));	
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (do_cd(cmd->args, &env));
	return (1);
}
