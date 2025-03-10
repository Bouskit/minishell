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
	char	*var;
	struct s_env	*prev;
	struct s_env	*next;		
}	t_env;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_token_type//add builtin
{
	WORD,
	PIPE,
	R_IN,
	R_OUT,
	HEREDOC,
	APPEND,
	ERROR_TOKEN
}	t_token_type;

typedef struct	s_command
{
	char				*arg;
	char				*infile;
	char				*outfile;
	int					append;
	struct	s_command	*next;
};


int	main(int ac, char **av, char **env);

//set up the environment
t_env	*env_new_ele(char *env);
int		env_append(t_env **env, char *var);
t_env	*init_env(char **env);
t_env	*init_default_env();
void	free_env(t_env *env);
void	print_env(t_env *env);



#endif