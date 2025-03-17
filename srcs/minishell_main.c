#include "../include/minishell.h"

#include <stdio.h>

void print_commands(t_command *cmds)
{
    int i;
    int out_i;

    printf("\n🔹 Parsed Commands:\n");
    while (cmds)
    {
        printf("🔹 Command \n");

        // Print arguments
        if (cmds->args)
        {
            i = 0;
            while (cmds->args[i])
            {
                printf("  Arguments:%d \"%s\" ", i, cmds->args[i]);
                i++;
            }
        }
        printf("\n");

        // Print input redirection
        if (cmds->infile)
            printf("  Input File: \"%s\"\n", cmds->infile);

		 // Print append flags
		 if (cmds->rout.append)
		 {
			 printf("  Append Flags: ");
			 for (int j = 0; j < out_i; j++)
				 printf("%d ", cmds->rout.append[j]);
			 printf("\n");
		 }
        // Print output redirection
        if (cmds->rout.outfile)
        {
            out_i = 0;
            while (cmds->rout.outfile[out_i])
            {
                printf("  Output Files %d : \"%s\" ", out_i,cmds->rout.outfile[out_i]);
                out_i++;
            }
            printf("\n");
        }

        // Print heredocs
        if (cmds->heredoc)
        {
            i = 0;
            while (cmds->heredoc[i])
            {
                printf("  Heredoc Delimiters: %d\n\"%s\" ",i, cmds->heredoc[i]);
                i++;
            }
            printf("\n");
        }

        // Move to the next command
        cmds = cmds->next;
        printf("\n");
    }
}


int	main(int argc, char **argv, char **envp)
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
		tokens = tokenization (cmd_line);
		free (cmd_line);
		if (!tokens)
			continue;
		check_syntax(tokens);
		cmds = parse_tokens(tokens);
		if (!cmds)
		{
			free_tokens(tokens);
			continue;
		}
		print_commands(cmds);
		free_tokens(tokens);
		free_cmd(cmds);
	}
	free_env(env);
	return (0);
}



//----------------------------------test 1&2
/*int	main(int argc, char **argv, char **envp)
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

