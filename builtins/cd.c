/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:42:48 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/15 01:19:25 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	my_perror(char *a1, char *a2, char *a3)
{
	if (a1)
		ft_putstr_fd(a1, 1);
	if (a2)
		ft_putstr_fd(a2, 1);
	if (a3)
		ft_putstr_fd(a3, 1);
	perror("");
}

void	update_pwd(char *pwd, char *name, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

int	do_cd(char **args, t_env **env)
{
	char	old[256];
	char	new[256];

	if (!args[1])
	{
		printf("minishell: %s: cd with only a relative or absolute path\n",
			args[0]);
		return (1);
	}
	if (args[2])
	{
		printf("minishell: %s: too many arguments\n", args[0]);
		return (1);
	}
	getcwd(old, 256);
	if (chdir(args[1]))
	{
		my_perror("minishell: cd: ", args[1], ": ");
		return (1);
	}
	getcwd(new, 256);
	update_pwd(old, "OLDPWD", env);
	update_pwd(new, "PWD", env);
	return (0);
}
