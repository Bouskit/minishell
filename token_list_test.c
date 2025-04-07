#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if(!new)
		return (NULL);
	new->next = NULL;
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free_tokens(new);
		return (NULL);
	}
	new->type = type;
	return (new);
}

t_token	*split_token(t_token **token)// split by quotations, aaa$aa'bb$bb b'"cc$cc cc"->token1->aaa$aa, token 2->bb$bb b, token 3->cc$cc cc 
{
	int			i;
	char		*tmp;
	t_token 	*var;
	int			start;

	i = 0;
	while ((*token)->value[i])
	{
		if ((*token)->value[i] != '\'')
		{
			tmp =  extract_quoted_string((*token)->value[i], &i, '\'');
			if (!add_token(&var, new_token(tmp, SINGLE_QUOTES)))
			{
				free_tokens(var);
				return (NULL);
			}
			free (tmp);
			i++;
		}
		else if ((*token)->value[i] != '"')
		{
			tmp =  extract_quoted_string((*token)->value[i], &i, '"');
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
			while ((*token)->value[i] && (*token)->value[i] != '"' && (*token)->value[i] != '\'')
				i++;
			tmp = ft_strndup(&(*token)->value[start], i - start);
			if (!add_token(&var, new_token(tmp, WORD)))
			{
				free_tokens(var);
				return (NULL);
			}
			free (tmp);
		}
	}
}



