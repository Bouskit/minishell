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
	struct s_env *next;
}t_env;

//-------------- BUILTINS ----------------

void builtins_env(t_env *e);
void builtins_pwd(t_env *e);
void builtins_exit(char *input, t_status *status);
void builtins_export(char *input, t_env *e);
void builtins_echo(char *input);


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