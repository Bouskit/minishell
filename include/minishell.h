/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:44:25 by bboukach          #+#    #+#             */
/*   Updated: 2025/03/20 22:45:02 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft_custom/libft.h"
#include <sys/wait.h>

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
}t_env;

typedef struct s_out
{
	int				*append;      
    char			**outfile;     
} t_out;

typedef struct s_in
{
	int				*heredoc;
	char			**infile;
} t_in;

typedef struct	s_command
{
	char				**args;
	t_out				rout;
	t_in				rin;
	int					index;
	struct	s_command	*next;
}	t_command;

/////ENV/////

void free_env(t_env *env);
void free_doublechar(char **str);
t_env	*env_last(t_env *e);
t_env	*env_new(char *name, char *value);
void 	env_addback(t_env **env, t_env *new);
int		env_size(t_env *lst);
t_env *init_env(char **envp);

//pipe

void	close_all_pipes(int **pipes);
char **env_to_envp(t_env *env);
void	do_heredoc(int pipehd[2], char *limiter);
void redir_out(t_out *rout);
void	redir_in(t_in *rin);
void	child_command(t_command *cmd, t_env *env);
void	execute_pipe(t_command *cmd, t_env *env);
void execute_one_command(t_command *cmd, t_env *env);
void	execute(t_command *cmd, t_env *env);

//path
char *path_env(t_env *env);
char	*add_at_the_end(char *path, char *cmd);
char	**add_cmd_to_paths(char **paths, char *cmd);
char *find_path(char *cmd, t_env *env);

//utils

int cmd_size(t_command *cmd);

#endif