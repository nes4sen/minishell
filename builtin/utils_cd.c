#include "../parsing/minishell.h"

char *find_home_repert(t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->name, "HOME") == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

int    cd_zero_arg(char *tmp, char *pwd_now, char *cur,t_env *env)
{
    tmp = find_home_repert(env);
    if(tmp != NULL)
    {
        if(chdir(tmp) == -1)
        {
            printf("cd: no such file or directory: %s\n", tmp);
            return(free(pwd_now), -1);
        }
        update_env(&env, "OLDPWD", pwd_now);
        cur = getcwd(NULL, 0);
        if(!cur)
        {
            perror("getcwd");
            return(free(pwd_now), -1);
        }
        update_env(&env, "PWD", cur);
        free(cur);
    }
    else
    {
        printf("cd: HOME not set\n");
        return(free(pwd_now), -1);
    }
    return(0);
}

int    cd_whith_1p(char *pwd_now, char *cur, t_env *env)
{
    // Pas besoin de chdir(pwd_now);
    update_env(&env, "OLDPWD", pwd_now);
    cur = getcwd(NULL, 0);
    if(!cur)
    {
        perror("getcwd");
        return(free(pwd_now), -1);
    }
    update_env(&env, "PWD", cur);
    free(cur);
    return(0);
}

int    cd_whith_2p(char *pwd_now, char *cur, t_env *env)
{
    if (chdir("..") == -1)
    {
        printf("cd: no such file or directory: %s\n", "..");
        free(pwd_now);
        return(-1);
    }
    update_env(&env, "OLDPWD", pwd_now);
    cur = getcwd(NULL, 0);
    if(!cur)
    {
        perror("getcwd");
        return(free(pwd_now), -1);
    }
    update_env(&env, "PWD", cur);
    free(cur);
    return(0);
}

int    cd_with_arg(char **arg, char *pwd_now, char *cur, t_env *env)
{
    int status;

    status = 0;
    if(ft_strcmp(".", arg[1]) == 0)
        status = cd_whith_1p(pwd_now, cur, env);
    else if(ft_strcmp("..", arg[1]) == 0)
        status = cd_whith_2p(pwd_now, cur, env);
    else
    {
        if (chdir(arg[1]) == -1)
        {
            printf("cd: no such file or directory: %s\n", arg[1]);
            return(free(pwd_now), -1);
        }
        update_env(&env, "OLDPWD", pwd_now);
        cur = getcwd(NULL, 0);
        if(!cur)
        {
            perror("getcwd");
            return(free(pwd_now), -1);
        }
        update_env(&env, "PWD", cur);
        free(cur);
    }
    return(status);
}
