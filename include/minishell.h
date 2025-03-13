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
	WORD,
	PIPE,
	R_IN,// <: Redirects a file’s content as input to a command. "cat < file.txt"
	HEREDOC,// <<
	R_OUT,//>: Overwrites the file with the command’s output."echo "Hello" > file.txt
	APPEND,//>>: Appends the output to the file instead of overwriting.
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
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
	char				*infile;
	char				*outfile;
	int					append;
	struct	s_command	*next;
}	t_command;

typedef struct s_redir
{
    int type;       // TOKEN_OUTPUT, TOKEN_APPEND, TOKEN_INPUT, TOKEN_HEREDOC
    char *file;     // The filename or heredoc delimiter
    struct s_redir *next;
} t_redir;

typedef struct s_mini
{
	t_env			*env;
	t_token			*tokens;
	t_command		*cmds;
	struct s_mini	*next;
}	t_mini;

extern	t_mini	*mini;

int	main(int ac, char **av, char **env);

//set up the environment
t_env	*env_new_ele(char *env);
int		add_env(t_env **env, char *var);
t_env	*init_env(char **env);
t_env	*init_default_env();
void	free_env(t_env *env);
void	print_env(t_env *env);


//utils
void *ft_realloc(void *ptr, size_t new_size);
char *ft_strndup(const char *s, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);



#endif