#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void display_prompt(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input) // Handle Ctrl+D (EOF)
        {
            printf("exit\n");
            break;
        }
        if (*input)
            add_history(input); // Save to history
        free(input);
    }
}

int	main()
{
	display_prompt();
	return (0);
}
