/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:14:15 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/20 23:52:41 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute_pipe(t_command *cmd, t_env *env)
{
    pid_t pid;
    int status;
    int **pipes;
    int i = 0;
    int num_cmds = cmd_size(cmd);

    if (!(pipes = create_pipes(num_cmds)))
		return;
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
    while (i < num_cmds)
    {
        waitpid(-1, &status, 0);
        i++;
    }
    close_all_pipes(pipes);
}

void execute_one_command(t_command *cmd, t_env *env) 
{
    pid_t pid;
    int status;
    char *path;
    char **env_array;

    pid = fork();
    if (pid == 0) 
	{
        env_array = env_to_envp(env);
        path = find_path(cmd->args[0], env);

        redir_in(&cmd->rin);
        redir_out(&cmd->rout);

        execve(path, cmd->args, env_array);
    } 
    waitpid(pid, &status, 0);
}

void	execute(t_command *cmd, t_env *env)
{
	if (cmd_size(cmd) > 1)
		execute_pipe(cmd, env);
	else 
		execute_one_command(cmd, env);
}