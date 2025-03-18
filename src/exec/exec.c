/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:35:58 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/18 17:29:30 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipes(int pipes[2][2], int i)
{
	if 
}

void	do_heredoc(int i, int pipes[2][2])
{
	char *line;
	char *limiter;

	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		write(1, ">", 2);
		line = get_next_line(0);
		if (!line || (ft_strcmp(line, limiter) == 0))
			break;
		write(pipes[i % 2][0], line, ft_strlen(line));
		free(line);
	}
	free(line);
	free(limiter);
	close(pipes[i % 2][0]);
	return;
}

int redir_out(t_command *cmd, int i, int pipes[2][2])
{
	int i = 0;
	int fd = -1;

	if(cmd->rout.outfile)
	{
		while(cmd->rout.outfile[i])
		{
			if (fd != -1)
				close (fd);
			
		}
	}
}


int	redir_in(t_command *cmd, int i, int pipes[2][2])
{
	int i = 0;
	int fd = -1;

	if (cmd->heredoc)
	{
		while (cmd->heredoc[i])
		{
			do_heredoc(i, pipes);
			i++;
		}
		dup2(pipes[i % 2][0], STDIN_FILENO);
		return (1);
	}

	if (cmd->infile)
	{
		while (cmd->infile[i])
		{
			if (fd != -1)
				close (fd);
			fd = open(cmd->infile[i], O_RDONLY);
			if (fd < 0)
				perror(cmd->infile[i]);
			i++;
		}
		if (fd != -1)
			dup2(fd, STDIN_FILENO);
		else 
			dup2(open("/dev/null", O_RDONLY), STDIN_FILENO);
		return (1);
	}
	return (0);
}

void	child_command(t_command *cmd, int i, int pipes[2][2])
{
	char **argve; 
	
	if (!(redir_in(cmd, i, pipes)))
		if (i > 0)
			dup2(pipes[(i + 1) % 2][0], STDIN_FILENO);

	if (!(redir_out(cmd, i, pipes)))
		if (cmd->next)
			dup2(pipes[i % 2][1], STDOUT_FILENO);
			
	close_pipes(pipes, i);
	if ((execve(cmd->args[0], cmd->args, envp)) == -1)
		return 1;

}

void	execute_pipe(t_command *cmd)
{
	pid_t pid;
	int pipes[2][2];
	int i = 0;

	while (cmd)
	{
		if (cmd->next)
			if (pipe(pipes[i % 2]) < 0)
				exit(1);
		if ((pid = fork()) < 0)
			exit(1);
		if (pid == 0)
			child_command(cmd, i, pipes);
		close_pipes(pipes, i);
		cmd = cmd->next;
		i++;
	}
	waitpid(-1, &status, 0);
}

