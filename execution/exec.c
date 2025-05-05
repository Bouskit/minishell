/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:14:15 by bboukach          #+#    #+#             */
/*   Updated: 2025/05/04 23:05:25 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_parent_pipes(int **pipes, int num_cmds, int i)
{
	if (i > 0)
		close(pipes[i - 1][0]);
	if (i < num_cmds - 1)
		close(pipes[i][1]);
}

int	execute_pipe(t_command *cmd, t_env *env, int exit_code)
{
	pid_t			pid;
	int				**pipes;
	int				num_cmds;
	t_command		*head;

	num_cmds = cmd_size(cmd);
	pipes = create_pipes(num_cmds);
	if (!pipes)
		return (1);
	head = cmd;
	pid = pipe_loop(cmd, env, pipes, num_cmds);
	if (pid == 127)
		return (127);
	return (wait_exitcode(pipes, num_cmds, pid, exit_code));
}

void	child_command(t_command *head, t_command *cmd, t_env *env)
{
	char	*path;
	char	**env_array;
	int		ret;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	if (cmd->args[0] && (ft_strcmp(cmd->args[0], "./minishell") == 0
			|| ft_strcmp(cmd->args[0], "minishell") == 0))
		increment_shlvl(&env);
	env_array = env_to_envp(env);
	if (redir_in_and_out(cmd) < 0)
		free_exitcode(head, env, env_array, 1);
	if (is_builtin(cmd->args[0]))
	{
		ret = execute_builtin(cmd, env);
		free_exitcode(head, env, env_array, ret);
	}
	path = command_path(head, cmd, env, env_array);
	signal(SIGQUIT, &sigf);
	execve(path, cmd->args, env_array);
	perror("minishell:");
	free_exitcode(head, env, env_array, 127);
}

int	special_case(t_command *cmd, int exit_code)
{
	int	stdin_cpy;
	int	stdout_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	stdout_cpy = dup(STDOUT_FILENO);
	redir_in_and_out(cmd);
	dup2(stdin_cpy, STDIN_FILENO);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdin_cpy);
	close(stdout_cpy);
	return (exit_code);
}

int	execute(t_command *cmd, t_env *env)
{
	int	exit_code;

	exit_code = 0;
	g_interactive = 1;
	if (!cmd->args || !cmd->args[0])
	{
		exit_code = special_case(cmd, exit_code);
		g_interactive = 0;
		return (exit_code);
	}
	if (cmd_size(cmd) > 1)
		exit_code = execute_pipe(cmd, env, exit_code);
	else
		exit_code = execute_one_command(cmd, env, exit_code);
	g_interactive = 0;
	return (exit_code);
}
