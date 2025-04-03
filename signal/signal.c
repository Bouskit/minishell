/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:53:30 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/03 18:15:39 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t g_in_execution = 0;

void sig_handler_interactive(int signo)
{
    if (signo == SIGINT) 
    {
        write(STDOUT_FILENO, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void sig_handler_exec(int signo)
{
    // Dans ce mode, on laisse simplement le signal être propagé aux enfants
    if (signo == SIGINT)
        write(STDOUT_FILENO, "\n", 1);
}

// À appeler avant d'entrer en mode interactif (prompt)
void setup_interactive_signals(void)
{
    g_in_execution = 0;
    signal(SIGINT, sig_handler_interactive);
    signal(SIGQUIT, SIG_IGN);  // Ignore Ctrl-
}

// À appeler avant d'exécuter une commande
void setup_exec_signals(void)
{
    g_in_execution = 1;
    signal(SIGINT, sig_handler_exec);
    signal(SIGQUIT, SIG_IGN);  
}
	