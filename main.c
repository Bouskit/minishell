/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:14:22 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/20 23:53:23 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_env *e;
	t_status *status = malloc(sizeof(t_status));
	char *input;

	(void)ac;
	(void)av;
	
	e = init_env(envp);
	status->exit_code = 0;
	
	while (1)
	{
		if(!(input = readline("minishell$ ")))
		{
			printf("exit\n");
			exit(0);
		}
		add_history(input);
		do_input(input, e, status);
	}
	free(status);
	free_env(e);
	return (0);
}