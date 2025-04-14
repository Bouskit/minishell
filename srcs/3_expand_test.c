/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:24:21 by xiazhang          #+#    #+#             */
/*   Updated: 2025/04/13 15:00:24 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
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
}*/

#include "../include/minishell.h"

// Fonctions utilitaires existantes mais optimisées
int isquote(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
            return 1;
        i++;
    }
    return 0;
}

int isdollar(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == '$')
            return 1;
        i++;
    }
    return 0;
}

int dollar_in_normal(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == '$')
            return 1;
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
        if (s[i])  // Éviter les dépassements si on a atteint la fin
            i++;
    }
    return 0;
}

int dollar_in_dq(char *s)
{
    int i = 0;
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
                    return 1;
                i++;
            }
        }
        if (s[i])
            i++;
    }
    return 0;
}

// Vérifie si un mot contient du contenu à expanser ($ ou quotes)
int contains_expandable_content(char *str)
{
    return (isdollar(str) || isquote(str));
}

// Extraction d'une chaîne entre quotes
char *extract_quoted_string(char *cmd_line, int *i, char quote_type)
{
    int start = ++(*i);
    int len = 0;
    
    while (cmd_line[*i] && cmd_line[*i] != quote_type)
    {
        (*i)++;
        len++;
    }
    
    char *result = ft_substr(cmd_line, start, len);
    if (!result)
    {    
        ft_putstr_fd("Error: Failed to malloc\n", 2);
        return NULL;
    }
    
    return result;
}

// Supprime toutes les quotes d'une chaîne
char *remove_quotes(char *str)
{
    char *result = malloc(strlen(str) + 1);
    if (!result)
        return NULL;
    
    int i = 0, j = 0;
    char quote_type = 0;
    
    while (str[i])
    {
        if ((str[i] == '\'' || str[i] == '"'))
        {
            if (quote_type == 0)
                quote_type = str[i];
            else if (quote_type == str[i])
                quote_type = 0;
            else
                result[j++] = str[i];
        }
        else 
        {
            result[j++] = str[i];
        }
        i++;
    }
    
    result[j] = '\0';
    return result;
}

// Libération d'un tableau de chaînes
void free_string_array(char **arr)
{
    if (!arr)
        return;
    
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}

// Divise une chaîne par types de quotes
t_token *split_by_quotes(char *str)
{
    t_token *result = NULL;
    int i = 0;
    
    while (str[i])
    {
        if (str[i] == '\'')
        {
            int start = ++i;
            int len = 0;
            
            while (str[i] && str[i] != '\'')
            {
                i++;
                len++;
            }
            
            char *content = ft_substr(str, start, len);
            if (!content)
                goto error_cleanup;
                
            if (!add_token(&result, new_token(content, SINGLE_QUOTES)))
            {
                free(content);
                goto error_cleanup;
            }
            free(content);
            
            if (str[i])
                i++;
        }
        else if (str[i] == '"')
        {
            int start = ++i;
            int len = 0;
            
            while (str[i] && str[i] != '"')
            {
                i++;
                len++;
            }
            
            char *content = ft_substr(str, start, len);
            if (!content)
                goto error_cleanup;
                
            if (!add_token(&result, new_token(content, DOUBLE_QUOTES)))
            {
                free(content);
                goto error_cleanup;
            }
            free(content);
            
            if (str[i])
                i++;
        }
        else
        {
            int start = i;
            int len = 0;
            
            while (str[i] && str[i] != '\'' && str[i] != '"')
            {
                i++;
                len++;
            }
            
            char *content = ft_substr(str, start, len);
            if (!content)
                goto error_cleanup;
                
            if (!add_token(&result, new_token(content, WORD)))
            {
                free(content);
                goto error_cleanup;
            }
            free(content);
        }
    }
    
    return result;

error_cleanup:
    free_tokens(result);
    return NULL;
}

// Ajoute le token de code de sortie
void add_exit_status_token(t_token **dest_list, int exit_code)
{
    char exit_code_str[16];
    snprintf(exit_code_str, sizeof(exit_code_str), "%d", exit_code);
    
    if (!add_token(dest_list, new_token(exit_code_str, WORD)))
    {
        ft_putstr_fd("Error: Failed to add exit status token\n", 2);
    }
}

// Ajoute une variable d'environnement expansée
void add_expanded_var(t_token **dest_list, char *var_name, t_env *env)
{
    if (!var_name || !var_name[0])
    {
        // Si var_name est vide, on ajoute juste le signe $ littéral
        if (!add_token(dest_list, new_token("$", WORD)))
            ft_putstr_fd("Error: Failed to add $ token\n", 2);
        return;
    }
    
    t_env *current = env;
    int found = 0;
    
    // Chercher la variable dans l'environnement
    while (current)
    {
        if (!strcmp(var_name, current->name))
        {
            if (!add_token(dest_list, new_token(current->value, WORD)))
                ft_putstr_fd("Error: Failed to add env var token\n", 2);
            found = 1;
            break;
        }
        current = current->next;
    }
    
    // Si la variable n'est pas trouvée, ajouter une chaîne vide
    if (!found)
    {
        if (!add_token(dest_list, new_token("", WORD)))
            ft_putstr_fd("Error: Failed to add empty token\n", 2);
    }
}

// Expansion des variables dans une partie du token
void expand_dollar_in_part(t_token **dest_list, t_token *part, t_env *env, int exit_code)
{
    // Cas spécial: juste un $ tout seul
    if (part->value[0] == '$' && !part->value[1])
    {
        if (!add_token(dest_list, new_token("$", WORD)))
            ft_putstr_fd("Error: Failed to add $ token\n", 2);
        return;
    }
    
    char **dollar_parts = ft_split(part->value, '$');
    if (!dollar_parts)
    {
        ft_putstr_fd("Error: Failed to split by $\n", 2);
        return;
    }
    
    // Si la chaîne commence par $
    if (part->value[0] == '$')
    {
        // Cas spécial $?
        if (part->value[1] == '?')
        {
            add_exit_status_token(dest_list, exit_code);
            // Si après $? il y a d'autres caractères
            if (part->value[2])
            {
                char *remainder = ft_strdup(part->value + 2);
                if (remainder)
                {
                    if (!add_token(dest_list, new_token(remainder, WORD)))
                        ft_putstr_fd("Error: Failed to add remainder token\n", 2);
                    free(remainder);
                }
            }
        }
        else
        {
            // Pour ignorer le caractère $ initial
            char *var_name = part->value + 1;
            // Trouver la fin du nom de la variable (premiers caractères alphanumériques et underscore)
            int var_len = 0;
            while (var_name[var_len] && (isalnum(var_name[var_len]) || var_name[var_len] == '_'))
                var_len++;
            
            char *extracted_var = ft_substr(var_name, 0, var_len);
            if (extracted_var)
            {
                add_expanded_var(dest_list, extracted_var, env);
                free(extracted_var);
                
                // S'il y a du texte après la variable
                if (var_name[var_len])
                {
                    char *remainder = ft_strdup(var_name + var_len);
                    if (remainder)
                    {
                        if (!add_token(dest_list, new_token(remainder, WORD)))
                            ft_putstr_fd("Error: Failed to add remainder token\n", 2);
                        free(remainder);
                    }
                }
            }
        }
    }
    else if (dollar_parts && dollar_parts[0])
    {
        // La partie avant le premier $ est un texte littéral
        if (!add_token(dest_list, new_token(dollar_parts[0], WORD)))
            ft_putstr_fd("Error: Failed to add text token\n", 2);
    }
    
    // Traiter les parties restantes
    if (dollar_parts)
    {
        for (int i = 1; dollar_parts[i]; i++)
        {
            if (dollar_parts[i][0] == '?')
            {
                add_exit_status_token(dest_list, exit_code);
                if (strlen(dollar_parts[i]) > 1)
                {
                    char *remainder = ft_strdup(dollar_parts[i] + 1);
                    if (remainder)
                    {
                        if (!add_token(dest_list, new_token(remainder, WORD)))
                            ft_putstr_fd("Error: Failed to add remainder token\n", 2);
                        free(remainder);
                    }
                }
            }
            else
            {
                // Trouver la fin du nom de la variable
                int var_len = 0;
                while (dollar_parts[i][var_len] && (isalnum(dollar_parts[i][var_len]) || dollar_parts[i][var_len] == '_'))
                    var_len++;
                
                char *var_name = ft_substr(dollar_parts[i], 0, var_len);
                if (var_name)
                {
                    add_expanded_var(dest_list, var_name, env);
                    free(var_name);
                    
                    // S'il y a du texte après la variable
                    if (dollar_parts[i][var_len])
                    {
                        char *remainder = ft_strdup(dollar_parts[i] + var_len);
                        if (remainder)
                        {
                            if (!add_token(dest_list, new_token(remainder, WORD)))
                                ft_putstr_fd("Error: Failed to add remainder token\n", 2);
                            free(remainder);
                        }
                    }
                }
            }
        }
        free_string_array(dollar_parts);
    }
}

// Gestion de l'expansion des variables
void expand_variables_in_word(t_token **dest_list, t_token *src_token, t_env *env, int exit_code)
{
    t_token *quote_parts = split_by_quotes(src_token->value);
    if (!quote_parts)
    {
        ft_putstr_fd("Error: Failed to split by quotes\n", 2);
        return;
    }
    
    t_token *current_part = quote_parts;
    while (current_part)
    {
        if (current_part->type == SINGLE_QUOTES)
        {
            // Le contenu entre single quotes est littéral
            if (!add_token(dest_list, new_token(current_part->value, WORD)))
                ft_putstr_fd("Error: Failed to add single quoted token\n", 2);
        }
        else if (current_part->type == DOUBLE_QUOTES || current_part->type == WORD)
        {
            // Expansion des variables dans les double quotes ou text normal
            expand_dollar_in_part(dest_list, current_part, env, exit_code);
        }
        current_part = current_part->next;
    }
    
    free_tokens(quote_parts);
}

// Expansion d'un mot avec variables ou quotes
void expand_and_add_word(t_token **dest_list, t_token *src_token, t_env *env, int exit_code)
{
    if (isdollar(src_token->value) && 
        (dollar_in_dq(src_token->value) || dollar_in_normal(src_token->value)))
    {
        expand_variables_in_word(dest_list, src_token, env, exit_code);
    }
    else if (isquote(src_token->value))
    {
        // Traitement des quotes sans variables
        char *unquoted = remove_quotes(src_token->value);
        if (unquoted)
        {
            if (!add_token(dest_list, new_token(unquoted, WORD)))
                ft_putstr_fd("Error: Failed to add unquoted token\n", 2);
            free(unquoted);
        }
    }
    else
    {
        // Mot simple sans expansion nécessaire
        if (!add_token(dest_list, new_token(src_token->value, WORD)))
            ft_putstr_fd("Error: Failed to add simple word token\n", 2);
    }
}

// Fonction principale d'expansion
t_token *expand_tokens(t_token *token_list, t_env *env, int exit_code)
{
    t_token *expanded_list = NULL;
    t_token *current = token_list;
    
    while (current)
    {
        // Gestion différente selon le type de token
        if (current->type == WORD)
        {
            if (contains_expandable_content(current->value))
                expand_and_add_word(&expanded_list, current, env, exit_code);
            else
            {
                if (!add_token(&expanded_list, new_token(current->value, WORD)))
                {
                    free_tokens(expanded_list);
                    return NULL;
                }
            }
        }
        else
        {
            // Les tokens qui ne sont pas des WORD sont ajoutés tels quels
            if (!add_token(&expanded_list, new_token(current->value, current->type)))
            {
                free_tokens(expanded_list);
                return NULL;
            }
        }
        current = current->next;
    }
    
    return expanded_list;
}