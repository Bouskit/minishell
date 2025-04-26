/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:55:40 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/26 17:07:41 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>//printf
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft_custom/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>

extern int	g_interactive;

typedef struct s_status
{
	int	exit_code;
}				t_status;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;		
}				t_env;

typedef enum e_token_type//add builtin
{
	WORD,//0
	PIPE,//1 |
	R_IN,//2 <
	HEREDOC,//3 <<
	R_OUT,//4 >
	APPEND,//5 >>
	SINGLE_QUOTES,//6
	DOUBLE_QUOTES,//7
	EXIT_STATUS,
	VAR,
	ERROR = -2
}				t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct s_command
{
	char				**args;
	int					*in;
	char				**infile;
	int					*append;
	char				**outfile;
	int					index;
	int					exit_code;
	struct s_command	*next;
}				t_command;

typedef struct s_index
{
	int	ac;
	int	out_i;
	int	in_i;
	int	cmd_count;
}				t_index;

typedef struct s_mini
{
	t_env			*env;
	t_token			*tokens;
	t_command		*cmds;
	char			*cmd_line;
	int				exit_code;
}				t_mini;

typedef enum e_quote
{
	NONE,
	SQUOTE,
	DQUOTE
}				t_quote;

typedef struct s_expand
{
	char		*input;
	int			i;
	char		*result;
	t_env		*env;
	int			exit_code;
	t_quote		state;
	int			status;
}				t_expand;

void			print_commands(t_command *cmds);
int				main(int ac, char **av, char **env);

//set up the environment
t_env			*env_new_ele(char *env);
int				add_env(t_env **env, t_env *new);
t_env			*init_env(char **envp);
t_env			*init_default_env(void);
void			free_env(t_env *env);
void			print_env(t_env *env);

//tokenization
t_token			*new_token(char *value, t_token_type type);
int				add_token(t_token **tokens, t_token *new);
t_token_type	operator_type(char	*str);
int				ft_is_space(char c);
int				is_operator(char c);
void			skip_quoted_word(char *line, int *i, char quote);
char			*extract_word(char *line, int *i);
int				unclosed_quote(char	*cmd_line);
bool			handle_operator(const char *line, int *i, t_token **tokens);
bool			handle_word(char *line, int *i, t_token **tokens);
t_token			*tokenization(char *cmd_line);
t_token			*tokenization(char *cmd_line);

//expand variables
char			*append_char_safe(char *s1, char c);
char			*str_append(char *s1, const char *s2);
char			*get_env_value(t_env *env, char *name);
void			append_exit_status(t_expand *exp);
void			extract_var(t_expand *exp);
void			handle_dollar(t_expand *exp);
void			char_none(t_expand *exp);
void			char_squotes(t_expand *exp);
void			char_dquotes(t_expand *exp);
void			init_expand(t_expand *exp,
					char *input, t_env *env, int exit_code);
char			*finalize_expand(t_expand *exp);
char			*expand_word(char *input, t_env *env, int exit_code);
int				word_token(t_token **expanded,
					t_token *current, t_env *env, int exit_code);
int				non_word_token(t_token **expanded, t_token *current);
t_token			*expand_tokens(t_token *token_list, t_env *env, int exit_code);

//parsing
int				empty_line(char *cmd_line);
int				check_syntax(t_token *tokens);
t_command		*new_command(int index);
int				add_command(t_command **cmds, t_command *new);
int				add_cmd_args(t_command **cmds, t_token **token, int *ac);
int				add_cmd_outfile(t_command **cmd, t_token **token, int *out_i);
int				add_cmd_infile(t_command **cmd, t_token **token, int *in_i);
t_token			*init_parsing(char *cmd_line,
					t_env *env, int exit_code, t_index *num);
bool			handle_pipe(t_command **cmd,
					t_command **first_cmd, t_index *num);
bool			handle_non_pipe(t_command **cmd,
					t_token **tokens, t_index *num);
t_command		*parse_tokens(char *cmd_line, t_env *env, int exit_code);

//utils
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char			*ft_strndup(const char *s, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);

//free all kinds
void			free_env(t_env *env);
void			free_tokens(t_token *tokens);
void			free_cmd(t_command *cmd);

t_token			*expand_tokens(t_token *token, t_env *env, int exit_code);
//----------------------------- BILAL -----------------------------

//-------------------------- EXECUTION ----------------------------
// exec

int	execute_pipe(t_command *cmd, t_env *env, int exit_code);
void	child_command(t_command *cmd, t_env *env);
int special_case(t_command *cmd, int exit_code);
int	execute(t_command *cmd, t_env *env);

void	redir_in_and_out(t_command *cmd);
void	free_exitcode(t_command *cmd, t_env *env, char **env_array,
		int exitcode);
void	close_unused_pipes(int **pipes, int num_cmds, int i);
char	*command_path(t_command *cmd, t_env *env, char **env_array);
int	wait_exitcode(int **pipes, int num_cmds, pid_t last_pid, int exit_code);

int	execute_one_builtin(t_command *cmd, t_env *env, int exit_code);
int	execute_one_command(t_command *cmd, t_env *env, int exit_code);

//redirections

void			redir_in(t_command *cmd);
void			redir_out(t_command *cmd);
void			redir_pipes(int num_cmds, int i, int **pipes);

//path

char			*path_env(t_env *env);
char			*add_at_the_end(char *path, char *cmd);
char			**add_cmd_to_paths(char **paths, char *cmd);
char			*find_path(char *cmd, t_env *env);

//utils_exec

void			close_all_pipes(int **pipes);
char			**env_to_envp(t_env *env);
int				**create_pipes(int nb_cmd);
void			do_heredoc(int pipehd[2], char *limiter);
int				cmd_size(t_command *cmd);

//-------------------------- BUILTINS ----------------------------

int				is_builtin(char *name);
int				execute_builtin(t_command *cmd, t_env *env);
void			my_perror(char *a1, char *a2, char *a3);
void			update_pwd(char *pwd, char *name, t_env **env);
int				do_cd(char **args, t_env **env);
void			echo_no_option(char **args);
void			echo_option(char **args);
int				do_echo(char **args);
int				do_env(t_env *e);
int				do_exit(char **args);
void			new_var(char *args, t_env **e);
int				export_equal(char *args);
void			export_print(t_env *e);
void			export_sort(t_env *e);
int 			special_case(t_command *cmd, int exit_code);
int				do_export(char **args, t_env **e);
int				do_pwd(void);
void			unset_var(char *args, t_env **e);
int				do_unset(char **args, t_env **e);

//-------------------------- UTILS ----------------------------

int				str_is_num(char *str);
void			free_doublechar(char **str);
void			ft_putstr3(char *a1, char *a2, char *a3, int fd);

t_env			*env_last(t_env *e);
t_env			*env_new(char *name, char *value);
void			env_addback(t_env **env, t_env *new);
int				env_size(t_env *lst);
void			increment_shlvl(t_env **env);
t_env			*init_env(char **envp);

//sig
void			sigf(int signal);
void			handle_sig(void);

#endif