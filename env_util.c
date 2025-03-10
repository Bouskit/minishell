#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For getcwd()
#include <limits.h>  // For PATH_MAX

typedef struct s_env
{
    char            *var;
    struct s_env    *next;
    struct s_env    *prev;
}   t_env;

/* ✅ Create a new environment variable node */
t_env *env_new_elem(char *var)
{
    t_env *new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->var = strdup(var);
    if (!new->var)
    {
        free(new);
        return (NULL);
    }
    new->next = new;
    new->prev = new;
    return (new);
}

/* ✅ Append a new variable to the environment list */
int env_append(t_env **env, char *var)
{
    t_env *new = env_new_elem(var);
    t_env *tail;

    if (!new)
        return (0);
    if (!(*env))  // If list is empty, new becomes head
        *env = new;
    else
    {
        tail = (*env)->prev;
        tail->next = new;
        new->prev = tail;
        new->next = *env;
        (*env)->prev = new;
    }
    return (1);
}

/* ✅ Initialize environment from envp */
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

/* ✅ Handle empty envp by setting default variables */
t_env *init_default_env(void)
{
    t_env *env = NULL;
    char path[PATH_MAX];

    if (!env_append(&env, strdup("OLDPWD=")))
    {
        free_env(env);
        return (NULL);
    }
    if (getcwd(path, PATH_MAX))
    {
        char *pwd = malloc(strlen("PWD=") + strlen(path) + 1);
        if (pwd)
        {
            strcpy(pwd, "PWD=");
            strcat(pwd, path);
            env_append(&env, pwd);
        }
    }
    return (env);
}

/* ✅ Print the environment list (for debugging) */
void print_env(t_env *env)
{
    t_env *tmp;

    if (!env)
        return;
    tmp = env;
    do
    {
        printf("%s\n", tmp->var);
        tmp = tmp->next;
    } while (tmp != env);
}

/* ✅ Free the entire environment list */
void free_env(t_env *env)
{
    t_env *tmp;
    t_env *start;

    if (!env)
        return;
    start = env;

    while (env)  // ✅ Safe condition
    {
        tmp = env->next;  // ✅ Move to next node BEFORE freeing
        free(env->var);
        free(env);
        env = tmp;  // ✅ Now, env is safe to use
        if (env == start) // ✅ Stop when we've freed all nodes
            break;
    }
}

