/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:15:25 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/17 14:17:35 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_infile(int *fd, int *pipehd, char *infile, int is_heredoc)
{
    if (is_heredoc)
    {
        pipe(pipehd);
        do_heredoc(pipehd, infile);
    }
    else
    {
        if (*fd != -1)
            close(*fd);
        *fd = open(infile, O_RDONLY);
        if (*fd < 0)
        {
            perror(infile);
            exit(1);
        }
    }
}

void redir_in(t_command *cmd)
{
    int x = 0;
    int fd = -1;
    int pipehd[2];

    if (cmd->infile && cmd->infile[0])
    {
        while (cmd->infile[x])
        {
            handle_infile(&fd, pipehd, cmd->infile[x], cmd->in[x]);
            x++;
        }
        if (cmd->in[x - 1])
        {
            dup2(pipehd[0], STDIN_FILENO);
            close(pipehd[0]);
        }
        else 
            dup2(fd, STDIN_FILENO);
        if (fd > 0)
            close(fd);
    }
}

void redir_out(t_command *cmd)
{
	int x = 0;
	int fd = -1;

	if (cmd->outfile && cmd->outfile[0])
	{
		while(cmd->outfile[x])
		{
			if (fd != -1)
				close(fd);
			if (cmd->append[x])
				fd = open(cmd->outfile[x], O_WRONLY | O_CREAT | O_APPEND, 0644);
			else 
				fd = open(cmd->outfile[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				perror(cmd->outfile[x]);
			x++;
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd);
	}
	return;
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
