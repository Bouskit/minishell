/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:55:40 by xiazhang          #+#    #+#             */
/*   Updated: 2025/03/06 13:55:50 by xiazhang         ###   ########.fr       */
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
#include "libft.h"

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
	char				**infile;
	t_out				rout;
	char				**heredoc;
	int					index;
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
t_command		*new_command();
int				add_command(t_command **cmds, t_command *new);
t_command		*parse_tokens(t_token *tokens);

//utils
void 	*ft_realloc(void *ptr, size_t new_size);
char 	*ft_strndup(const char *s, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

//free all kinds
void	free_env(t_env *env);
void	free_tokens(t_token *tokens);
void	free_cmd(t_command *cmds);


#endif