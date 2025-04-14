#include "../include/minishell.h"

#include <stdio.h>


void	print_token(t_token	*tokens)
{
	printf("\n🔹 tokens:\n");
	while (tokens)
    {
		printf("Token: [%s] Type: [%d]\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
}
void print_commands(t_command *cmds)
{
	int in_i;
	
    while (cmds)
    {
		printf("🔹 Command %d\n", cmds->index);
		
        // Print arguments
        if (cmds->args)
        {
			int i = 0;
            while (cmds->args[i])
            {
				printf("  Arguments%d: \"%s\" ", i, cmds->args[i]);
                i++;
            }
			printf("\n");
        }
        
		
        // Print input flags
        if (cmds->in)
		{
			in_i = 0;
			while (cmds->in[in_i] != -5)
			{
				printf("  Input Flag %d: \"%d\" ", in_i, cmds->in[in_i]);
				in_i++;
			}
			printf("\n");
		}
		// Print input file
		if (cmds->infile)
		{
			int in_f = 0;
			while (cmds->infile[in_f])
			{
				printf("  Input Files %d : \"%s\" ", in_f,cmds->infile[in_f]);
				in_f++;
			}
			printf("\n");
			printf("\n");
		}
		
		// Print append flags
		if (cmds->append)
		{
			int out_a = 0;
			while (cmds->append[out_a] != -5)
			{
				printf ("  Append Flag %d : \"%d\" ", out_a,cmds->append[out_a]);
				out_a++;
			}
			printf("\n");
		}
        // Print output redirection
        if (cmds->outfile)
        {
			int out_o = 0;
            while (cmds->outfile[out_o])
            {
				printf("  Output Files %d : \"%s\" ", out_o, cmds->outfile[out_o]);
                out_o++;
            }
            printf("\n");
        }
        // Move to the next command
        cmds = cmds->next;
    }
}


int g_interactive = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	char	*cmd_line;
	t_token	*tokens; 
	t_command	*cmds;
	t_token	*expanded;
	int exit_code;
	
	handle_sig();
	exit_code = 0;
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
		{
			printf("exit\n");
			break ;
		}
		add_history(cmd_line);
		tokens = tokenization (cmd_line);
		free (cmd_line);
		if (!tokens)
			continue;
		if (!check_syntax(tokens))
		{
			free_tokens(tokens);
			continue;
		}
		expanded = expand_tokens(tokens, env, exit_code);
		if (!expanded)
		{
			free_tokens(tokens);
			continue;
		}
		cmds = parse_tokens(expanded);
		if (!cmds)
		{
			free_tokens(tokens);
			continue;
		}
		//print_token(tokens);
		//print_commands(cmds);
		free_tokens(tokens);
		free_tokens(expanded);
		exit_code = execute(cmds, env);
		free_cmd(cmds);
	}
	free_env(env);
	return (exit_code);
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

