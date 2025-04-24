/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:14:15 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/24 16:54:37 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redir_in_and_out(t_command *cmd)
{
	redir_in(cmd);
	redir_out(cmd);
}

void	free_exitcode(t_command *cmd, t_env *env, char **env_array,
		int exitcode)
{
	free_cmd(cmd);
	free_env(env);
	free_doublechar(env_array);
	exit(exitcode);
}

void	close_unused_pipes(int **pipes, int num_cmds, int i)
{
	int	j;

	j = 0;
	while (j < num_cmds - 1)
	{
		if (j != i - 1)
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
		j++;
	}
}

char	*command_path(t_command *cmd, t_env *env, char **env_array)
{
	char	*path;

	path = NULL;
	if (access(cmd->args[0], F_OK) == 0)
	{
		if (access(cmd->args[0], X_OK) == 0)
			path = ft_strdup(cmd->args[0]);
		else
		{
			ft_putstr3("minishell: ", cmd->args[0], ": Permission denied\n", 2);
			free_exitcode(cmd, env, env_array, 126);
		}
	}
	else if (!(path = find_path(cmd->args[0], env)))
	{
		ft_putstr3("minishell: ", cmd->args[0], ": command not found\n", 2);
		free_exitcode(cmd, env, env_array, 127);
	}
	return (path);
}

int	wait_exitcode(int **pipes, int num_cmds, pid_t last_pid, int exit_code)
{
	int		i;
	int		status;
	pid_t	current_pid;

	i = 0;
	close_all_pipes(pipes);
	while (i < num_cmds)
	{
		current_pid = waitpid(-1, &status, 0);
		if (current_pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (exit_code);
}

int	execute_pipe(t_command *cmd, t_env *env, int exit_code)
{
	pid_t	pid;
	int		**pipes;
	int		i;
	int		num_cmds;

	i = 0;
	num_cmds = cmd_size(cmd);
	if (!(pipes = create_pipes(num_cmds)))
		return (1);
	while (cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			redir_pipes(num_cmds, i, pipes);
			close_unused_pipes(pipes, num_cmds, i);
			child_command(cmd, env);
		}
		if (i > 0)
			close(pipes[i - 1][0]);
		if (i < num_cmds - 1)
			close(pipes[i][1]);
		cmd = cmd->next;
		i++;
	}
	return (wait_exitcode(pipes, num_cmds, pid, exit_code));
}

void	child_command(t_command *cmd, t_env *env)
{
	char	*path;
	char	**env_array;

	if (cmd->args[0] && (ft_strcmp(cmd->args[0], "./minishell") == 0
			|| ft_strcmp(cmd->args[0], "minishell") == 0))
		increment_shlvl(&env);
	env_array = env_to_envp(env);
	redir_in_and_out(cmd);
	if (is_builtin(cmd->args[0]))
	{
		free_doublechar(env_array);
		exit(execute_builtin(cmd, env));
	}
	path = command_path(cmd, env, env_array);
	execve(path, cmd->args, env_array);
	perror("minishell:");
	free_exitcode(cmd, env, env_array, 127);
}

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

int special_case(t_command *cmd, int exit_code)
{
	int stdin_cpy;
	int stdout_cpy;

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
