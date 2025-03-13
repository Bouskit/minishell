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
		printf("Error: Failed to initialize environment\n");
		return (1);
	}
	while (1)
	{
		cmd_line = readline ("$minishell ");
		if (!cmd_line)
		{
			free_env(env);
			break ;
		}
		add_history(cmd_line);
		tokens = tokenization (cmd_line);
		parse_tokens(tokens);

	}

	free_env(env);
	return (0);
}
