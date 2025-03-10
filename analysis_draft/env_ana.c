t_env *init_env(char **envp)
{
    t_env *env = NULL;
    int i = 0;

    if (!envp || !envp[0])
        return (init_default_env());  // Handle empty env

    while (envp[i])
    {
        if (!env_append(&env, envp[i]))
        {
            free_env(env);
            return (NULL);
        }
        i++;
    }
    return (env);
}
