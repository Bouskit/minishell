/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:53:30 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/26 17:37:22 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void sigf(int signal)
{
    if (signal == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        if (g_interactive == 0)
            rl_redisplay();
    }
    else if (signal == SIGQUIT)
    {
        ft_putstr_fd("^\\Quit (core dumped)\n", STDERR_FILENO);
    }
}

void handle_sig(void)
{   
    signal(SIGINT, &sigf);
    signal(SIGQUIT, SIG_IGN);
}
