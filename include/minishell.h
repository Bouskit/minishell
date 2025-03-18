#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft_custom/libft.h"

typedef struct s_status
{
	int exit_code;
}t_status;

typedef struct s_env
{
	char *name;
	char *value;
	//struct *prev;
	struct s_env *next;
}t_env;

typedef enum e_token_type//add builtin
{
	WORD,//0
	PIPE,//1 |
	R_IN,//2 <: Redirects a file’s content as input to a command. "cat < file.txt"
	HEREDOC,//3 <<
	R_OUT,//4 >: Overwrites the file with the command’s output."echo "Hello" > file.txt
	APPEND,//5 >>: Appends the output to the file instead of overwriting.
	QUOTE_SINGLE,//6
	QUOTE_DOUBLE,//7
	ERROR = -2
}	t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_out
{
	int				*append;      
    char			**outfile;     
} t_out;

typedef struct	s_command
{
	char				**args;
	char				*infile;
	t_out				rout;
	char				**heredoc;
	int					index;
	struct	s_command	*next;
}	t_command;

//-------------- BUILTINS ----------------

void builtins_env(t_env *e);
void builtins_pwd(t_env *e);
void builtins_exit(char **args, t_status *status);
void builtins_export(char **args, t_env **e);
void builtins_echo(char **args);


void do_input(char *input, t_env *e, t_status *status);

//-------------- ENV ---------------------

void free_doublechar(char **str);
void free_env(t_env *env);
t_env	*env_last(t_env *e);
t_env	*env_new(char *name, char *value);
void env_addback(t_env **env, t_env *new);
t_env *init_env(char **envp);

//-------------- UTILS -------------------
int	strcmp_space(char *s1, char *s2);
int str_is_num(char *str);
int	env_size(t_env *lst);




#endif