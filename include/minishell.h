/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:55:40 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/16 20:04:06 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>//printf
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft_custom/libft.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

extern int g_interactive;

typedef struct s_status
{
	int exit_code;
}t_status;

typedef struct s_env
{
	char	*name;
	char	*value;
	//struct s_env	*prev;
	struct s_env	*next;		
}	t_env;

typedef enum e_token_type//add builtin
{
	WORD,//0
	PIPE,//1 |
	R_IN,//2 <: Redirects a file’s content as input to a command. "cat < file.txt"
	HEREDOC,//3 <<
	R_OUT,//4 >: Overwrites the file with the command’s output."echo "Hello" > file.txt
	APPEND,//5 >>: Appends the output to the file instead of overwriting.
	SINGLE_QUOTES,//6
	DOUBLE_QUOTES,//7
	EXIT_STATUS,
	VAR,
	ERROR = -2
}	t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct	s_command
{
	char				**args;
	int					*in;
	char				**infile;
	int					*append;
	char				**outfile;
	int					index;
	int 				exit_code;
	struct	s_command	*next;
}	t_command;


/*typedef struct s_mini
{
	t_env			*env;
	t_token			*tokens;
	t_command		*cmds;
	struct s_mini	*next;
}	t_mini;

extern	t_mini	*mini;*/

void print_commands(t_command *cmds);
int	main(int ac, char **av, char **env);

//set up the environment
t_env	*env_new_ele(char *env);
int		add_env(t_env **env, t_env *new);
t_env	*init_env(char **envp);
t_env	*init_default_env();
void	free_env(t_env *env);
void	print_env(t_env *env);//------------test helper function

//tokenization
t_token			*new_token(char *value, t_token_type type);
int				add_token(t_token **tokens, t_token *new);
t_token_type	operator_type(char	*str);
int				ft_is_space(char c);
int				is_operator(char c);
t_token			*tokenization(char *cmd_line);

//parsing
int				check_syntax(t_token *tokens);
t_command		*new_command(int index);
int				add_command(t_command **cmds, t_command *new);
int add_cmd_args(t_command **cmds, t_token **token, int *ac);
int	add_cmd_outfile(t_command **cmd, t_token **token, int *out_i);
int	add_cmd_infile(t_command **cmd, t_token **token, int *in_i);
t_command		*parse_tokens(t_token *tokens);

//utils
void 	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char 	*ft_strndup(const char *s, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

//free all kinds
void	free_env(t_env *env);
void	free_tokens(t_token *tokens);
void	free_cmd(t_command *cmd);


t_token	*expand_tokens(t_token *token, t_env *env, int exit_code);
//----------------------------- BILAL -----------------------------

//-------------------------- EXECUTION ----------------------------
// exec

int	execute_pipe(t_command *cmd, t_env *env, int exit_code);
void	child_command(t_command *cmd, t_env *env);
int    execute_one_builtin(t_command *cmd, t_env *env, int exit_code);
int	execute_one_command(t_command *cmd, t_env *env, int exit_code);
int	execute(t_command *cmd, t_env *env);

//redirections

void redir_in(t_command *cmd);
void redir_out(t_command *cmd);
void redir_pipes(int num_cmds, int i, int **pipes);

//path

char *path_env(t_env *env);
char	*add_at_the_end(char *path, char *cmd);
char	**add_cmd_to_paths(char **paths, char *cmd);
char *find_path(char *cmd, t_env *env);

//utils_exec

void	close_all_pipes(int **pipes);
char **env_to_envp(t_env *env);
int **create_pipes(int nb_cmd);
void	do_heredoc(int pipehd[2], char *limiter);
int cmd_size(t_command *cmd);

//-------------------------- BUILTINS ----------------------------

int is_builtin(char *name);
int execute_builtin(t_command *cmd, t_env *env);

void my_perror(char *a1, char *a2, char *a3);
void update_pwd(char *pwd, char *name, t_env **env);
int do_cd(char **args, t_env **env);

void echo_no_option(char **args);
void echo_option(char **args);
int do_echo(char **args);

int do_env(t_env *e);

int do_exit(char **args);

void new_var(char *args, t_env **e);
int export_equal(char *args);
void export_print(t_env *e);
void export_sort(t_env *e);
int do_export(char **args, t_env **e);

int do_pwd(void);

void unset_var(char *args, t_env **e);
int do_unset(char **args, t_env **e);

//-------------------------- UTILS ----------------------------

int str_is_num(char *str);
void free_doublechar(char **str);
void ft_putstr3(char *a1, char *a2, char *a3, int fd);

t_env	*env_last(t_env *e);
t_env	*env_new(char *name, char *value);
void env_addback(t_env **env, t_env *new);
int	env_size(t_env *lst);
void increment_shlvl (t_env **env);
t_env *init_env(char **envp);

//sig
void sigf(int signal);
void handle_sig(void);

#endif