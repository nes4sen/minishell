#include "../minishell.h"

int     help_env_fonc(t_env *env);

int     env_fonc(char **arg, t_env *env)
{
    int status;
    
    if(!env || !arg)
        return(-1);
    if(arg[1])
    {
        printf("env: %s: No such file or directory\n", arg[1]);
        return(-1);
    }
    status = help_env_fonc(env);
    return(status);
}

int     help_env_fonc(t_env *env)
{
    char *name_value;
    char *temp;

    while (env != NULL)
    {   
        temp = ft_strjoin(env->name, "=");
        if(!temp)
            return (-1);
        if(env->value)
        {
            name_value = ft_strjoin(temp, env->value);
            free(temp);
            if(!name_value)
                return (-1);
        }
        else
            name_value = temp;
        printf("%s\n", name_value);
        free(name_value);
        env = env->next;
    }
    return 0; 
}
