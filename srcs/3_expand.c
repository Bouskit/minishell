/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:36:48 by bboukach          #+#    #+#             */
/*   Updated: 2025/04/14 11:33:56 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

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

typedef enum e_quote
{
    NONE,
    SQUOTE,
    DQUOTE
}	t_quote;

typedef struct s_expand
{
    const char		*input;
    int				i;
    char			*result;
    t_env			*env;
    int				exit_code;
    t_quote 	    state;
    int				status;
}	t_expand;

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
    if (!var_name)
    {
        ft_putstr_fd("Error: ft_substr failed for var name\n", 2);
        exp->status = 1;
        return ;
    }
    var_value = get_env_value(exp->env, var_name);
    if (var_value)
        exp->result = str_append(exp->result, var_value);
    free(var_name);
    exp->i--;
    if (var_value && !exp->result)
        exp->status = 1;
}

void	handle_dollar(t_expand *exp)
{
    exp->i++;
    if (exp->input[exp->i] == '?')
        append_exit_status(exp);
    else if (ft_isalpha(exp->input[exp->i]) || exp->input[exp->i] == '_')
        extract_var(exp);
    else if (exp->input[exp->i] == '\0' || exp->input[exp->i] == '\''
        || exp->input[exp->i] == '"' || exp->input[exp->i] == ' ')
    {
        exp->result = append_char_safe(exp->result, '$');
        exp->i--;
    }
    else
    {
        exp->result = append_char_safe(exp->result, '$');
        exp->i--;
    }
    if (!exp->result && exp->status == 0)
        exp->status = 1;
}

void	char_none(t_expand *exp)
{
    char	current_char;

    current_char = exp->input[exp->i];
    if (current_char == '\'')
        exp->state = SQUOTE;
    else if (current_char == '"')
        exp->state = DQUOTE;
    else if (current_char == '$')
        handle_dollar(exp);
    else
    {
        exp->result = append_char_safe(exp->result, current_char);
        if (!exp->result)
            exp->status = 1;
    }
}

void	char_squotes(t_expand *exp)
{
    char	current_char;

    current_char = exp->input[exp->i];
    if (current_char == '\'')
        exp->state = NONE;
    else
    {
        exp->result = append_char_safe(exp->result, current_char);
        if (!exp->result)
            exp->status = 1;
    }
}

void	char_dquotes(t_expand *exp)
{
    char	current_char;

    current_char = exp->input[exp->i];
    if (current_char == '"')
        exp->state = NONE;
    else if (current_char == '$')
        handle_dollar(exp);
    else
    {
        exp->result = append_char_safe(exp->result, current_char);
        if (!exp->result)
            exp->status = 1;
    }
}

void	init_expand(t_expand *exp, char *input, t_env *env, int exit_code)
{
    exp->input = input;
    exp->env = env;
    exp->exit_code = exit_code;
    exp->result = NULL;
    exp->i = 0;
    exp->state = NONE;
    exp->status = 0;
}

char	*finalize_expand(t_expand *exp)
{
    if (exp->status != 0)
    {
        free(exp->result);
        return (NULL);
    }
    if (exp->result == NULL)
        return (ft_strdup(""));
    return (exp->result);
}

char	*expand_word(char *input, t_env *env, int exit_code)
{
    t_expand	exp;

    init_expand(&exp, input, env, exit_code);
    while (exp.input && exp.input[exp.i] && exp.status == 0)
    {
        if (exp.state == SQUOTE)
            char_squotes(&exp);
        else if (exp.state == DQUOTE)
            char_dquotes(&exp);
        else
            char_none(&exp);
        exp.i++;
    }
    return (finalize_expand(&exp));
}

int	word_token(t_token **expanded, t_token *current, t_env *env, int exit_code)
{
    char	*expanded_value;
    t_token	*new;

    expanded_value = expand_word(current->value, env, exit_code);
    if (!expanded_value)
        return (1);
    if (expanded_value[0] != '\0')
    {
        new = new_token(expanded_value, WORD);
        if (!new)
        {
            free(expanded_value);
            return (1);
        }
        if (!add_token(expanded, new))
        {
            free(expanded_value);
            free_tokens(new);
            return (1);
        }
    }
    free(expanded_value);
    return (0);
}

int	non_word_token(t_token **expanded, t_token *current)
{
    t_token	*new;

    new = new_token(current->value, current->type);
    if (!new)
        return (1);
    if (!add_token(expanded, new))
    {
        free_tokens(new);
        return (1);
    }
    return (0);
}

t_token	*expand_tokens(t_token *token_list, t_env *env, int exit_code)
{
    t_token	*expanded;
    t_token	*current;
    int		error_flag;

    expanded = NULL;
    current = token_list;
    error_flag = 0;
    while (current && error_flag == 0)
    {
        if (current->type == WORD)
            error_flag = word_token(&expanded, current, env, exit_code);
        else
            error_flag = non_word_token(&expanded, current);
        current = current->next;
    }
    if (error_flag != 0)
    {
        free_tokens(expanded);
        return (NULL);
    }
    return (expanded);
}

