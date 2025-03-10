#include "env.c"


typedef struct s_env
{
    char            *var;
    struct s_env    *next;
    struct s_env    *prev;
}   t_env;

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
}

