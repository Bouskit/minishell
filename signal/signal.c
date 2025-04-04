/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:53:30 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/04 17:10:33 by bboukach         ###   ########.fr       */
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
}

void handle_sig(void)
{   
    signal(SIGINT, &sigf);
    signal(SIGQUIT, SIG_IGN);  
}
	