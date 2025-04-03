/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:14:15 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/03 18:16:26 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_pipe(t_command *cmd, t_env *env, int exit_code)
{
	pid_t	pid;
	int		status;
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
			child_command(cmd, env);
		}
		if (i > 0)
			close(pipes[i - 1][0]);
		if (i < num_cmds - 1)
			close(pipes[i][1]);
		cmd = cmd->next;
		i++;
	}
	i = 0;
	close_all_pipes(pipes);
	while (i < num_cmds)
	{
		waitpid(-1, &status, 0);
		i++;
	}
    if (WIFEXITED(status))
        exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        exit_code = 128 + WTERMSIG(status);
    return (exit_code);
}

void	child_command(t_command *cmd, t_env *env)
{
	char	*path;
	char	**env_array;

	env_array = env_to_envp(env);
	redir_in(cmd);
	redir_out(cmd);
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd, env);
		free_doublechar(env_array);
		exit(0);
	}
	else
	{
		if (!(path = find_path(cmd->args[0], env)))
		{
			printf("minishell: %s: No such file or directory\n", cmd->args[0]);
			free_doublechar(env_array);
			exit(127);
		}
		execve(path, cmd->args, env_array);
		free_doublechar(env_array);
		exit(127);
	}
}

int    execute_one_builtin(t_command *cmd, t_env *env, int exit_code)
{
    int		stdin_cpy;
	int		stdout_cpy;

    stdin_cpy = dup(STDIN_FILENO);
    stdout_cpy = dup(STDOUT_FILENO);
    redir_in(cmd);
    redir_out(cmd);
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

	if (is_builtin(cmd->args[0]))
		return(execute_one_builtin(cmd, env, exit_code));
	pid = fork();
	if (pid == 0)
	{
		env_array = env_to_envp(env);
		redir_in(cmd);
		redir_out(cmd);
		if (!(path = find_path(cmd->args[0], env)))
		{
			printf("minishell: %s: No such file or directory\n", cmd->args[0]);
			free_doublechar(env_array);
			exit(127);
		}
		execve(path, cmd->args, env_array);
		free_doublechar(env_array);
		exit(127);
	}
	waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        exit_code = 128 + WTERMSIG(status);
    return (exit_code);
}

int	execute(t_command *cmd, t_env *env)
{
    int exit_code;
    
    exit_code = 0;
	setup_exec_signals();
	if (cmd_size(cmd) > 1)
		exit_code = execute_pipe(cmd, env, exit_code);
	else
		exit_code = execute_one_command(cmd, env, exit_code);
	setup_interactive_signals();
    return (exit_code);
}