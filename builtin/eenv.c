#include "../parsing/minishell.h"


int     env_fonc(char **arg, t_env *env)
{
    int status;
    
    if(!env || !arg)
        return(-1);
    if(arg[1])
    {
        printf("env: %s: No such file or directory\n", arg[1]);
        return(127);
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
        if(env->value == NULL)
            env = env->next;
        else
        {
            temp = ft_strjoin(env->name, "=");
            if(!temp)
                return (-1);
            name_value = ft_strjoin(temp, env->value);
            // free(temp);
            if(!name_value)
                return (-1);
            printf("%s\n", name_value);
            // free(name_value);
            env = env->next;
        }
    }
    return 0; 
}
