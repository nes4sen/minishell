#include "../minishell.h"

int     fonc_cd(char **arg, t_env *env)
{
    char    *tmp = NULL;
    char    *current_getcwd = NULL;
    char    *pwd_now;
    int     nombre_arg;
    int     status;

    if(!arg)
        return(-1);
    nombre_arg = get_nbr_arg(arg);
    pwd_now = getcwd(NULL, 0);
    if(nombre_arg == 1)
        status = cd_zero_arg(tmp, pwd_now, current_getcwd, env);
    else if(nombre_arg == 2)
        status = cd_with_arg(arg, pwd_now, current_getcwd, env);
    else
    {
        printf("cd: too many arguments\n");
        return(free(pwd_now), -1);
    }
    free(pwd_now);
    return(status);
}

void    update_env(t_env **env, const char *name, const char *value)
{
    t_env   *current = *env;

    while (current)
    {
        if (ft_strcmp(current->name, (char*)name) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    add_back_env(env, (char*)name, (char*)value, (idx_nod(*env) + 1));
}

int     get_nbr_arg(char    **arg)
{
    int i = 0;

    while (arg[i])
        i++;
    return(i);
}