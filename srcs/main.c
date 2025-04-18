/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:52:34 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/14 15:38:19 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	g_interactive = 0;

static int	init_main(t_mini *mini, int argc, char **argv, char **envp)
{
	(void)argc, (void)argv;
	mini->env = NULL;
	mini->tokens = NULL;
	mini->cmds = NULL;
	mini->exit_code = 0;
	handle_sig();
	mini->env = init_env(envp);
	if (!mini->env)
	{
		ft_putstr_fd("Error: Failed to initialize environment\n", 2);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	if (!init_main(&mini, argc, argv, envp))
		return (1);
	while (1)
	{
		mini.cmd_line = readline ("$minishell ");
		if (!mini.cmd_line)
		{
			printf("exit\n");
			break ;
		}
		add_history(mini.cmd_line);
		mini.cmds = parse_tokens(mini.cmd_line, mini.env, mini.exit_code);
		if (!mini.cmds)
		{
			free_cmd(mini.cmds);
			continue ;
		}
		mini.exit_code = execute(mini.cmds, mini.env);
		free_cmd(mini.cmds);
	}
	free_env(mini.env);
	return (mini.exit_code);
}
