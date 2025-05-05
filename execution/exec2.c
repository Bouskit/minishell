/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:58:42 by bboukach          #+#    #+#             */
/*   Updated: 2025/05/04 23:07:25 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_in_and_out(t_command *cmd)
{
	if (redir_in(cmd) < 0)
		return (-1);
	redir_out(cmd);
	return (0);
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

char	*command_path(t_command *head, t_command *cmd, t_env *env, char **enva)
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
			free_exitcode(head, env, enva, 126);
		}
	}
	else
	{
		path = find_path(cmd->args[0], env);
		if (!path)
		{
			ft_putstr3("minishell: ", cmd->args[0], ": command not found\n", 2);
			free_exitcode(head, env, enva, 127);
		}
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
