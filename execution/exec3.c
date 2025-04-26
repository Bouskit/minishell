/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:00:16 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/26 17:38:17 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_one_builtin(t_command *cmd, t_env *env, int exit_code)
{
	int	stdin_cpy;
	int	stdout_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	stdout_cpy = dup(STDOUT_FILENO);
	redir_in_and_out(cmd);
	exit_code = execute_builtin(cmd, env);
	dup2(stdin_cpy, STDIN_FILENO);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdin_cpy);
	close(stdout_cpy);
	return (exit_code);
}

int	execute_one_command(t_command *cmd, t_env *env, int exit_code)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**env_array;

	if (!cmd->args || !cmd->args[0])
		return (special_case(cmd, exit_code));
	if (is_builtin(cmd->args[0]))
		return (execute_one_builtin(cmd, env, exit_code));
	pid = fork();
	if (pid == 0)
	{
		if (cmd->args[0] && (ft_strcmp(cmd->args[0], "./minishell") == 0
				|| ft_strcmp(cmd->args[0], "minishell") == 0))
			increment_shlvl(&env);
		env_array = env_to_envp(env);
		redir_in_and_out(cmd);
		path = command_path(cmd, env, env_array);
		signal(SIGQUIT, &sigf);
		execve(path, cmd->args, env_array);
		free_exitcode(cmd, env, env_array, 127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	return (exit_code);
}
