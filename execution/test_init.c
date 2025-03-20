/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:17:47 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/20 23:54:01 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command *init_cmd(void)
{
    t_command *cmd1, *cmd2, *cmd3;

    // Commande 1 : cat < infile1 << LIMITER
    cmd1 = malloc(sizeof(t_command));
    cmd1->args = malloc(2 * sizeof(char *));
    cmd1->args[0] = strdup("cat");
    cmd1->args[1] = NULL;

    cmd1->rin.infile = malloc(2 * sizeof(char *));
    cmd1->rin.infile[0] = strdup("infile1");
    cmd1->rin.infile[1] = NULL;

    cmd1->rin.heredoc = malloc(2 * sizeof(int));
    cmd1->rin.heredoc[0] = 0; // Pas de heredoc pour infile1
    cmd1->rin.heredoc[1] = 1; // Heredoc activé pour LIMITER

    cmd1->rin.infile = realloc(cmd1->rin.infile, 3 * sizeof(char *));
    cmd1->rin.infile[1] = strdup("LIMITER");
    cmd1->rin.infile[2] = NULL;

    cmd1->rout.outfile = NULL; // Pas de redirection de sortie
    cmd1->rout.append = NULL; // Pas de mode append

    cmd1->next = NULL;

    // Commande 2 : wc -w
    cmd2 = malloc(sizeof(t_command));
    cmd2->args = malloc(3 * sizeof(char *));
    cmd2->args[0] = strdup("wc");
    cmd2->args[1] = strdup("-w");
    cmd2->args[2] = NULL;

    cmd2->rin.infile = NULL; // Pas de redirection d'entrée
    cmd2->rin.heredoc = NULL; // Pas de heredoc

    cmd2->rout.outfile = NULL; // Pas de redirection de sortie
    cmd2->rout.append = NULL; // Pas de mode append

    cmd2->next = NULL;

    // Commande 3 : cat >> outfile
    cmd3 = malloc(sizeof(t_command));
    cmd3->args = malloc(2 * sizeof(char *));
    cmd3->args[0] = strdup("cat");
    cmd3->args[1] = NULL;

    cmd3->rin.infile = NULL; // Pas de redirection d'entrée
    cmd3->rin.heredoc = NULL; // Pas de heredoc

    cmd3->rout.outfile = malloc(2 * sizeof(char *));
    cmd3->rout.outfile[0] = strdup("outfile");
    cmd3->rout.outfile[1] = NULL;

    cmd3->rout.append = malloc(2 * sizeof(int));
    cmd3->rout.append[0] = 1; // Mode append activé

    cmd3->next = NULL;

    // Lier les commandes
    cmd1->next = cmd2;
    cmd2->next = cmd3;

    return cmd1;
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	
	t_env *env;
	t_command *cmd = NULL;
	
	env = init_env(envp);
	cmd = init_cmd();
	execute(cmd, env);
	return (0);
}