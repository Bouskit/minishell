/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:15:25 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/20 23:52:27 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void redir_in(t_in *rin)
{
	int x = 0;
	int fd = -1;
	int pipehd[2];

	if (rin->infile && rin->infile[0])
	{
		while (rin->infile[x])
		{
			if (rin->heredoc[x])
			{
				pipe(pipehd);
				do_heredoc(pipehd, rin->infile[x]);
			}
			else
			{
				if (fd != -1)
					close (fd);
				fd = open(rin->infile[x], O_RDONLY);
				if (fd < 0)
				{
					perror(rin->infile[x]);
					return;
				}
			}
			x++;
		}
		if (rin->heredoc[x - 1])
		{
			dup2(pipehd[0], STDIN_FILENO);
			close(pipehd[0]);
		}
		else 
			dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return;
}

void redir_out(t_out *rout)
{
	int x = 0;
	int fd = -1;

	if (rout->outfile)
	{
		while(rout->outfile[x])
		{
			if (fd != -1)
				close(fd);
			if (rout->append[x])
				fd = open(rout->outfile[x], O_WRONLY | O_CREAT | O_APPEND, 0644);
			else 
				fd = open(rout->outfile[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(rout->outfile[x]);
				return;
			}
			x++;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return;
}

void child_command(t_command *cmd, t_env *env)
{
	char *path;
	char **env_array = env_to_envp(env);

	path = find_path(cmd->args[0], env);
	
	redir_in(&cmd->rin);
	redir_out(&cmd->rout);
	
	execve(path, cmd->args, env_array);
}


void redir_pipes(int num_cmds, int i, int **pipes)
{
	if (i == 0) 
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
	else if (i == num_cmds - 1) 
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
	} 
	else 
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
}