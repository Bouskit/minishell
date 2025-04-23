/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:36:48 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/17 17:15:20 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*append_char_safe(char *s1, char c)
{
	char	*new_str;
	char	to_append[2];
	size_t	s1_len;

	to_append[0] = c;
	to_append[1] = '\0';
	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	new_str = ft_strjoin(s1, to_append);
	if (!new_str)
	{
		if (s1_len > 0 || c != '\0')
			ft_putstr_fd("Error: append_char_safe failed\n", 2);
		free(s1);
		return (NULL);
	}
	free(s1);
	return (new_str);
}

char	*str_append(char *s1, const char *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	new_str = NULL;
	s1_len = 0;
	s2_len = 0;
	if (!s2)
		return (s1);
	s2_len = ft_strlen(s2);
	if (!s1)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	new_str = ft_strjoin(s1, s2);
	if (!new_str)
	{
		if (s1_len > 0 || s2_len > 0)
			ft_putstr_fd("Error: str_append_free failed\n", 2);
		free(s1);
		return (NULL);
	}
	free(s1);
	return (new_str);
}

char	*get_env_value(t_env *env, char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->name && name && ft_strcmp(current->name, name) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

void	append_exit_status(t_expand *exp)
{
	char	*exit_str;

	exit_str = ft_itoa(exp->exit_code);
	if (!exit_str)
	{
		ft_putstr_fd("Error: ft_itoa failed for exit status\n", 2);
		exp->status = 1;
		return ;
	}
	exp->result = str_append(exp->result, exit_str);
	free(exit_str);
	if (!exp->result && exp->exit_code != 0)
	{
		exp->status = 1;
	}
}

void	extract_var(t_expand *exp)
{
	int		start;
	int		len;
	char	*var_name;
	char	*var_value;

	start = exp->i;
	len = 0;
	while (exp->input[exp->i]
		&& (ft_isalnum(exp->input[exp->i]) || exp->input[exp->i] == '_'))
	{
		exp->i++;
		len++;
	}
	var_name = ft_substr(exp->input, start, len);
	var_value = get_env_value(exp->env, var_name);
	if (var_value)
		exp->result = str_append(exp->result, var_value);
	free(var_name);
	exp->i--;
	if (var_value && !exp->result)
		exp->status = 1;
}
