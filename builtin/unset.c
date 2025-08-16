#include "../parsing/minishell.h"

int     unset_fonc(char **arg, t_env **env)
{
    int     i;

	if(arg[1] == NULL)
		return(0);
    i = 1;
    while (arg[i])
    {
            delete_var_env(arg[i], env);
        i++;
    }
    return(0);
}



void     indx_nods(t_env **env)
{
    t_env *temp;
    int     i = 0;

    if(!env || !*env)
        return;
    temp = *env;
    while (temp != NULL)
    {
        temp->index = i++;
        temp = temp->next;
    }
}

void	delete_var_env(char *name, t_env **env)
{
    t_env *env_temp;
    t_env *rev = NULL;

    env_temp = *env;
	while (env_temp != NULL)
	{
		if(ft_strcmp(name, env_temp->name) == 0)
		{
            if(rev == NULL)
                delete_first_node(env);
            else
            {
                rev->next = env_temp->next;
                // free(env_temp->name);
                // free(env_temp->value);
                // free(env_temp);
                break;
            }
		}
        rev = env_temp;
		env_temp = env_temp->next;
	}
    indx_nods(env);
}

void    delete_first_node(t_env **env)
{
    // t_env   *temp;

    // temp = *env;
    *env = (*env)->next;
    // free(temp->name);
    // free(temp->value);
    // free(temp);
    indx_nods(env);
    return ;
}
