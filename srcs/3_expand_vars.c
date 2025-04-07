/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expand_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:24:21 by xiazhang          #+#    #+#             */
/*   Updated: 2025/03/31 12:24:23 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	isquote(char *s)
{
	int	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return(1);
		i++;
	}
	return (0);
}

int	isdollar(char *s)
{
	int	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return(1);
		i++;
	}
	return (0);
}



int	dollar_in_normal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		i++;
	}
	return (0);
}


int	dollar_in_dq(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
			{
				if (s[i] == '$')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

char	*extract_quoted_string(char *cmd_line, int *i, char half_quote)
{
	int		start;
	char	*result;
	int		len;

	start = ++(*i);
	len = 0;
	while (cmd_line[*i] && cmd_line[*i] != half_quote)
	{
		(*i)++;
		len++;
	}
	result = ft_substr(cmd_line, start, len);
	if (!result)
	{	
		ft_putstr_fd("Error: Failed to malloc\n", 2);
		return (NULL);
	}
	return (result);
}




void	*handle_no_expansion_quotes(t_token **token)
{
	int	i, j;
	char	quote;
	t_token	*cur;

	i = 0;
	j = 0;
	quote = 0;
	cur = *token;
	while (cur->value[i])
	{
		if (cur->value[i] == '\'' || cur->value[i] == '"')
		{
			if (quote == 0)
				quote = cur->value[i];
			else if (quote == cur->value[i])
				quote = 0;
			else
				cur->value[j++] = cur->value[i];//pour ecrire guillemet different que la premier
		}
		else
			cur->value[j++] = cur->value[i];
		i++;
	}
	return (cur);
}

t_token	*split_token(t_token **token)// split by quotations, aaa$aa'bb$bb b'"cc$cc cc"->token1->aaa$aa, token 2->bb$bb b, token 3->cc$cc cc 
{
	int			i;
	char		*tmp;
	t_token 	*var;
	int			start;
	t_token		*cur;

	var = NULL;
	i = 0;
	cur =  *token;
	while (cur->value[i])
	{
		if (cur->value[i] == '\'')
		{
			tmp =  extract_quoted_string(cur->value, &i, '\'');
			if (!add_token(&var, new_token(tmp, SINGLE_QUOTES)))
			{
				free_tokens(var);
				return (NULL);
			}
			free (tmp);
			i++;
		}
		else if (cur->value[i] == '"')
		{
			tmp =  extract_quoted_string(cur->value, &i, '"');
			if (!add_token(&var, new_token(tmp, DOUBLE_QUOTES)))
			{
				free_tokens(var);
				return (NULL);
			}
			free (tmp);
			i++;
		}
		else
		{
			start = i;
			while (cur->value[i] && cur->value[i] != '"' && cur->value[i] != '\'')
				i++;
			tmp = ft_strndup(&cur->value[start], i - start);
			if (!add_token(&var, new_token(tmp, WORD)))
			{
				free_tokens(var);
				return (NULL);
			}
			free (tmp);
		}
	}
	return (var);
}

t_token *split_var(t_token **var)
{
	t_token *var_name;
	char	**result;
	int		i;
	t_token	*cur;

	var_name = NULL;
	cur = *var;
	while (cur)
	{
		if (cur->type == WORD || cur->type ==  DOUBLE_QUOTES)
		{
			result = ft_split(cur->value, '$');
			if (!result[0])//quand la chaine est juste tout $$$$$
			{
				if (!add_token(&var_name, new_token(cur->value, WORD)))
				{
					free_tokens(var_name);
					return (NULL);
				}
				return (var_name);
			}
			i = 0;
			if (cur->value[0] == '$' && cur->value[1] == '?')
			{
				if (!add_token(&var_name, new_token(result[0], EXIT_STATUS)))
				{
					free_tokens(var_name);
					return (NULL);
				}
				i++;
			}
			else if (cur->value[0] == '$')
			{
				if (!add_token(&var_name, new_token(result[0], VAR)))
				{
					free_tokens(var_name);
					return (NULL);
				}
				i++;
			}
			else
			{
				if (!add_token(&var_name, new_token(result[0], WORD)))
				{
					free_tokens(var_name);
					return (NULL);
				}
				if (result [1])
					i++;
				else
					return (var_name);
			}
			while (result[i])
			{
				if (result[i][0] == '?')
				{
					if (!add_token(&var_name, new_token(result[i], EXIT_STATUS)))
					{
						free_tokens(var_name);
						return (NULL);
					}
				}
				else
				{
					if (!add_token(&var_name, new_token(result[i], VAR)))
					{
						free_tokens(var_name);
						return (NULL);
					}
				}
				free (result[i]);
				i++;
			}
		}
		cur = cur->next;
	}
	return (var_name);
}

t_token	*replace_var(t_token *var_name, t_env *env)
{
	t_token	*var_value;
	
	var_value = NULL;
	while (var_name)
	{
		if (var_name->type == EXIT_STATUS || var_name->type == WORD)
		{
			if (!add_token(&var_value, new_token(var_name->value, var_name->type)))
			{
				free_tokens(var_name);
				free_tokens(var_value);
				return (NULL);
			}
		}
		else
		{
			while (env)
			{
				if (!strcmp(var_name->value, env->name))
				{
					if (!add_token(&var_value, new_token(env->value, WORD)))
					{
						free_tokens(var_name);
						free_tokens(var_value);
						return (NULL);
					}
				}
				env = env->next;
			}
		}
		var_name = var_name->next;
	}
	return(var_value);
}


t_token	*expand_tokens(t_token *token, t_env *env)
{
	t_token *var;
	t_token	*cur;
	t_token	*expanded;
	t_token *var_value;
	t_token	*var_name;

	cur = token;
	while (cur)
	{
		if(cur->type == WORD)
		{
			if (isdollar(cur->value))
			{
				if (dollar_in_dq(cur->value) || dollar_in_normal(cur->value))
				{
					var = split_token(&token);
					while (var)
					{
						var_name = split_var(&var);
						var_value = replace_var(var_name, env);
						while (var_value)
						{
							if (!add_token(&expanded, new_token(var_value->value, var_value->type)))
							{
								free_tokens(var_value);
								return (NULL);
							}
							var_value = var_value->next;
						}
						var = var->next;
					}
				}
			}
			else if (isquote(cur->value))
			{
				handle_no_expansion_quotes(&token);
				if (!add_token(&expanded, new_token (token->value, WORD)))
				{
					free_tokens(expanded);
					return (NULL);
				}
			}
			else
			{
				if (!add_token(&expanded, new_token (token->value, WORD)))
				{
					free_tokens(expanded);
					return (NULL);
				}
			}
		}
		else
		{
			if (!add_token(&expanded, new_token (token->value, token->type)))
			{
				free_tokens(expanded);
				return (NULL);
			}
		}
		cur = token->next;
	}
	return (expanded);
}

