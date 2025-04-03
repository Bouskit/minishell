/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:19:29 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/02 22:28:22 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *path_env(t_env *env)
{
	t_env *temp = env;

	while (temp)
	{
		if(ft_strcmp(temp->name, "PATH") == 0)
			return(temp->value);
		temp = temp->next;
	}
	return(NULL);
}

char	*add_at_the_end(char *path, char *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(cmd) + ft_strlen(path) + 2));
	if (!tmp)
		return (NULL);
	while (path[i])
	{
		tmp[i] = path[i];
		i++;
	}
	tmp[i] = '/';
	i++;
	while (cmd[j])
	{
		tmp[i + j] = cmd[j];
		j++;
	}
	tmp[i + j] = '\0';
	return (tmp);
}

char	**add_cmd_to_paths(char **paths, char *cmd)
{
	int		i;
	char	**cmd_paths;

	i = 0;
	while (paths[i])
		i++;
	cmd_paths = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (paths[i])
	{
		cmd_paths[i] = add_at_the_end(paths[i], cmd);
		i++;
	}
	cmd_paths[i] = NULL;
	return (cmd_paths);
}

char *find_path(char *cmd, t_env *env)
{
	char **fullpath;
	char **path_with_cmd;
	char *tmp;
	int i;

	i = 0;
	if(!cmd)
		return (NULL);
	if (!(fullpath = ft_split(path_env(env), ':')))
		return NULL;
	path_with_cmd = add_cmd_to_paths(fullpath, cmd);
	while (path_with_cmd[i])
	{
		if (access(path_with_cmd[i], F_OK) == 0)
		{
			tmp = ft_strdup(path_with_cmd[i]);
			free_doublechar(path_with_cmd);
			free_doublechar(fullpath);
			return (tmp);
		}
		i++;
	}
	free_doublechar(fullpath);
	free_doublechar(path_with_cmd);
	return (NULL);
}