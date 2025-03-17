#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	char	*cmd_line;
	t_token	*tokens; 

	env = init_env(envp);
    if (!env)
	{
		ft_putstr_fd("Error: Failed to initialize environment\n", 2);
		return (1);
	}
	while (1)
	{
		cmd_line = readline ("$minishell ");
		if (!cmd_line)
			break ;
		add_history(cmd_line);
		tokens = tokenization (cmd_line);
		if (!tokens)
			continue;
		free (cmd_line);
		while (tokens)
		{
			printf("Token: [%s] Type: [%d]\n", tokens->value, tokens->type);
			tokens = tokens->next;
		}
		free_tokens(tokens);
	}

	free_env(env);
	return (0);
}

/*int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	char	*cmd_line;
	t_token	*tokens; 
	t_command	*cmds;

	env = init_env(envp);
    if (!env)
	{
		ft_putstr_fd("Error: Failed to initialize environment\n", 2);
		return (1);
	}
	while (1)
	{
		cmd_line = readline ("$minishell ");
		if (!cmd_line)
			break ;
		add_history(cmd_line);
		free (cmd_line);
		tokens = tokenization (cmd_line);
		if (!tokens)
			continue;
		cmds = parse_tokens(tokens);
		if (!cmds)
		{
			free_tokens(tokens);
			continue;
		}
		free_tokens(tokens);
		free_commands(cmds);


	}

	free_env(env);
	return (0);
}*/

//---------------------------------1_env test

/*void print_env(t_env *env)
{
    t_env *tmp;

    if (!env)
        return;
    tmp = env;
    do
    {
        if (!tmp->name || !tmp->value) // Check for NULL fields
        {
            fprintf(stderr, "Error: NULL environment variable detected\n");
            return;
        }
        printf("%s=", tmp->name);
        printf("%s\n", tmp->value);
        tmp = tmp->next;
    } while (tmp != env && tmp);  // Ensure tmp is not NULL
}

int main(int argc, char **argv, char **envp)
{
    t_env *env;

    (void)argc;
    (void)argv;
    env = init_env(envp);
    if (!env)
    {
        printf("Error: Failed to initialize environment\n");
        return (1);
    }

    printf("🔹 Minishell Environment Variables:\n");
    print_env(env);

    free_env(env);
    return (0);
}*/

//---------------------------------2_tokenization test

/*int main()
{
    char input[] = ">> < fd << > ";
    t_token *tokens = tokenization(input);
	t_token *temp = tokens;
    
    while (tokens)
    {
        printf("Token: [%s] Type: [%d]\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
	free_tokens(temp);
    return 0;
}*/

