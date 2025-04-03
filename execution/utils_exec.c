/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:16:18 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/03 00:56:00 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_all_pipes(int **pipes)
{
	int i = 0;

	if (!pipes)
		return;

	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

char **env_to_envp(t_env *env)
{
    int size;
	char **envp;
	int i;
	t_env *tmp;
	
	tmp = env;
	size = env_size(tmp);
    envp = malloc((size + 1) * sizeof(char *)); 
    if (!envp)
        return NULL;
    i = 0;
    while (tmp)
    {
        envp[i] = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(envp[i], tmp->value);
        tmp = tmp->next;
        i++;
    }
    envp[i] = NULL;
    return (envp);
}

int **create_pipes(int nb_cmd)
{
	int **pipes;
	int i = 0;

	if (nb_cmd <= 1)
		return (NULL);
	pipes = malloc(sizeof(int *) * nb_cmd);

	while (i < nb_cmd - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	pipes[i] = NULL;
	return(pipes);
}

void	do_heredoc(int pipehd[2], char *limiter)
{
	char *line;

	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		write(open("/dev/tty", O_WRONLY), "> ", 2);
		line = get_next_line(0);
		if (!line || (ft_strcmp(line, limiter) == 0))
		{
			if (!line)
				write(open("/dev/tty", O_WRONLY), "\n", 1);
			break;
		}
		write(pipehd[1], line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	free(line);
	close(pipehd[1]);
	return;
}

int cmd_size(t_command *cmd)
{
	t_command *tmp;

	tmp = cmd;
	int i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
